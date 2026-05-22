#include "raylib.h"
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <stdexcept>


class TextureManager
{
private:
    std::unordered_map<std::string, Texture2D> mTextures;

public:
    ~TextureManager()
    {
        for (auto& [_, tex] : mTextures)
        {
            UnloadTexture(tex);
        }
    }

    Texture2D& get(const std::string& path)
    {
        if (!mTextures.contains(path))
        {
            Texture2D tex = LoadTexture(path.c_str());
            if (tex.id == 0)
            {
                throw std::runtime_error("Failed to load texture: " + path);
            }
            mTextures[path] = tex;
        }
        return mTextures[path];
    }
};


class Node
{
public:
    enum class State
    {
        Blocked,
        Unblocked,
        Activated
    };

protected:
    Vector2 mPosition;
    State mState { State::Blocked };
    std::vector<std::unique_ptr<Node>> mChildren;

public:
    Node(Vector2 pos)
        : mPosition(pos)
    {
    }

    void addChild(std::unique_ptr<Node> child)
    {
        mChildren.push_back(std::move(child));
    }

    void unblock()
    {
        mState = State::Unblocked;
    }

    void block()
    {
        mState = State::Blocked;
        for (auto& c : mChildren)
        {
            c->block();
        }
    }

    const Vector2& getPosition() const
    {
        return mPosition;
    }

    Node* findClicked(Vector2 p)
    {
        if (contains(p))
        {
            return this;
        }

        for (auto& c : mChildren)
        {
            if (auto* res = c->findClicked(p))
            {
                return res;
            }
        }

        return nullptr;
    }    

    virtual bool contains(Vector2 p) const = 0;
    virtual void onClick(int mouseButton, int& freePoints) = 0;
    virtual void draw() const = 0;
    
    virtual ~Node() = default;
};


class HitNode : public Node
{
protected:
    float mRadius { 24.f };
    Texture2D* mTexture { nullptr };

public:
    HitNode(Vector2 pos, const std::string& icon, TextureManager& tm)
        : Node(pos)
    {
        mTexture = &tm.get(icon);
    }

    bool contains(Vector2 p) const override
    {
        float dx = p.x - mPosition.x;
        float dy = p.y - mPosition.y;
        return dx * dx + dy * dy <= mRadius * mRadius;
    }

    void onClick(int mouseButton, int& freePoints) override
    {
        if (mouseButton != MOUSE_BUTTON_LEFT) return;

        if (mState == State::Blocked) return;

        if (mState == State::Unblocked)
        {
            if (freePoints > 0)
            {
                mState = State::Activated;
                freePoints--;
                for (auto& c : mChildren)
                {
                    c->unblock();
                }
            }
        }
        else if (mState == State::Activated)
        {
            mState = State::Unblocked;
            
            freePoints++; 
            
            for (auto& c : mChildren)
            {
                c->block();
            }
        }
    }

    Color getColor() const
    {
        switch (mState)
        {
            case State::Blocked:   return {40, 40, 40, 255};
            case State::Unblocked: return {80, 80, 40, 255};
            case State::Activated: return {160, 160, 40, 255};
        }
        return WHITE;
    }

    void draw() const override
    {
        for (const auto& c : mChildren)
        {
            DrawLineEx(mPosition, c->getPosition(), 2.0f, getColor());
            c->draw();
        }

        DrawCircleV(mPosition, mRadius, getColor());

        if (mTexture)
        {
            DrawTextureEx(*mTexture,
                          { mPosition.x - mRadius, mPosition.y - mRadius },
                          0.0f,
                          (mRadius * 2) / mTexture->width,
                          WHITE);
        }
    }
};

class AccumulativeNode : public Node
{
private:
    int mCurrentLevel { 0 };
    int mMaxLevel { 1 };
    float mSize { 48.f }; // Сторона квадрата
    Texture2D* mTexture { nullptr };

public:
    AccumulativeNode(Vector2 pos, int maxLevel, const std::string& icon, TextureManager& tm)
        : Node(pos), mMaxLevel(maxLevel)
    {
        mTexture = &tm.get(icon);
    }

    bool contains(Vector2 p) const override
    {
        return (p.x >= mPosition.x - mSize / 2.f && p.x <= mPosition.x + mSize / 2.f &&
                p.y >= mPosition.y - mSize / 2.f && p.y <= mPosition.y + mSize / 2.f);
    }

    void onClick(int mouseButton, int& freePoints) override
    {
        if (mState == State::Blocked) return;

        if (mouseButton == MOUSE_BUTTON_LEFT)
        {
            if (mState == State::Unblocked && freePoints > 0)
            {
                mState = State::Activated;
                mCurrentLevel = 1;
                freePoints--;
                // Разблокируем детей
                for (auto& c : mChildren) c->unblock();
            }
            else if (mState == State::Activated && mCurrentLevel < mMaxLevel && freePoints > 0)
            {
                mCurrentLevel++;
                freePoints--;
            }
        }
        else if (mouseButton == MOUSE_BUTTON_RIGHT)
        {
            if (mState == State::Activated)
            {
                mCurrentLevel--;
                freePoints++;

                if (mCurrentLevel == 0)
                {
                    mState = State::Unblocked;
                    for (auto& c : mChildren) c->block();
                }
            }
        }
    }

    Color getColor() const
    {
        switch (mState)
        {
            case State::Blocked:   return {40, 40, 80, 255};
            case State::Unblocked: return {80, 40, 120, 255};
            case State::Activated: return {160, 40, 240, 255};
        }
        return WHITE;
    }

    void draw() const override
    {
        for (const auto& c : mChildren)
        {
            DrawLineEx(mPosition, c->getPosition(), 2.0f, getColor());
            c->draw();
        }

        DrawRectangleV({ mPosition.x - mSize / 2.f, mPosition.y - mSize / 2.f }, { mSize, mSize }, getColor());

        if (mTexture)
        {
            DrawTextureEx(*mTexture,
                          { mPosition.x - mSize / 2.f, mPosition.y - mSize / 2.f },
                          0.0f,
                          mSize / mTexture->width,
                          WHITE);
        }

        std::string lvlStr = std::to_string(mCurrentLevel) + "/" + std::to_string(mMaxLevel);
        int textWidth = MeasureText(lvlStr.c_str(), 16);
        DrawText(lvlStr.c_str(), (int)(mPosition.x - textWidth / 2.f), (int)(mPosition.y + mSize / 2.f + 4.f), 16, WHITE);
    }
    
    int resetAndReturnPoints() {
        int pointsToReturn = mCurrentLevel;
        mCurrentLevel = 0;
        mState = State::Blocked;
        for(auto& c : mChildren) {
        }
        return pointsToReturn;
    }
};

class SkillTree
{
protected:
    std::unique_ptr<Node> mRoot;
    int mFreeSkillPoints;

public:
    SkillTree(int startingPoints)
        : mFreeSkillPoints(startingPoints)
    {
    }

    virtual ~SkillTree() = default;

    void handleClicks(Vector2 mousePos, int mouseButton)
    {
        if (!mRoot) return;
        
        if (auto* node = mRoot->findClicked(mousePos))
        {
            node->onClick(mouseButton, mFreeSkillPoints);
        }
    }

    virtual void draw() const
    {
        if (mRoot)
        {
            mRoot->draw();
        }

        std::string pointsText = "Free Skill Points: " + std::to_string(mFreeSkillPoints);
        DrawText(pointsText.c_str(), 20, 20, 24, MAROON);
    }
};

class MageSkillTree : public SkillTree
{
public:
    MageSkillTree(int startingPoints, TextureManager& tm)
        : SkillTree(startingPoints)
    {
        auto rootNode = std::make_unique<HitNode>(Vector2{400, 600}, "icons/icon_lightning.png", tm);
        auto manaNode = std::make_unique<AccumulativeNode>(Vector2{250, 450}, 3, "icons/icon_shield.png", tm);
        auto intelNode = std::make_unique<AccumulativeNode>(Vector2{550, 450}, 5, "icons/icon_eye.png", tm);
        auto fireballNode = std::make_unique<HitNode>(Vector2{150, 300}, "icons/icon_bomb.png", tm);
        auto meteorNode = std::make_unique<HitNode>(Vector2{350, 300}, "icons/icon_meteorite.png", tm);
        auto blizzardNode = std::make_unique<HitNode>(Vector2{650, 300}, "icons/icon_lightning.png", tm);

        manaNode->addChild(std::move(fireballNode));
        manaNode->addChild(std::move(meteorNode));
        
        intelNode->addChild(std::move(blizzardNode));

        rootNode->addChild(std::move(manaNode));
        rootNode->addChild(std::move(intelNode));

        mRoot = std::move(rootNode);
        mRoot->unblock();
    }

    void draw() const override
    {
        SkillTree::draw();
        DrawText("CLASS: MAGE", 20, 55, 20, GOLD);
    }
};

std::unique_ptr<Node> createTree(TextureManager& tm)
{
    auto root = std::make_unique<HitNode>(Vector2{400, 500}, "icons/icon_lightning.png", tm);

    auto a = std::make_unique<HitNode>(Vector2{200, 400}, "icons/icon_shuriken.png", tm);
    auto b = std::make_unique<HitNode>(Vector2{400, 400}, "icons/icon_bomb.png", tm);
    auto c = std::make_unique<HitNode>(Vector2{600, 400}, "icons/icon_eye.png", tm);

    a->addChild(std::make_unique<HitNode>(Vector2{100, 200}, "icons/icon_shield.png", tm));
    a->addChild(std::make_unique<HitNode>(Vector2{200, 200}, "icons/icon_sword.png", tm));

    auto deep = std::make_unique<HitNode>(Vector2{600, 200}, "icons/icon_bomb.png", tm);
    deep->addChild(std::make_unique<HitNode>(Vector2{500, 100}, "icons/icon_shuriken.png", tm));

    b->addChild(std::make_unique<HitNode>(Vector2{400, 200}, "icons/icon_hand.png", tm));
    b->addChild(std::make_unique<HitNode>(Vector2{500, 200}, "icons/icon_meteorite.png", tm));
    b->addChild(std::move(deep));

    c->addChild(std::make_unique<HitNode>(Vector2{700, 200}, "icons/icon_eye.png", tm));

    root->addChild(std::move(a));
    root->addChild(std::move(b));
    root->addChild(std::move(c));

    return root;
}


int main()
{
    const int windowWidth = 800;
    const int windowHeight = 800;
    InitWindow(windowWidth, windowHeight, "Skill Tree");
    SetTargetFPS(60);

    TextureManager tm;
    
    std::unique_ptr<SkillTree> currentSkillTree = std::make_unique<MageSkillTree>(10, tm);

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            currentSkillTree->handleClicks(mouse, MOUSE_BUTTON_LEFT);
        }
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            currentSkillTree->handleClicks(mouse, MOUSE_BUTTON_RIGHT);
        }

        BeginDrawing();
        ClearBackground({15, 15, 20, 255});

        currentSkillTree->draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}