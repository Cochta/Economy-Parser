#include "MyImage.h"

void MyImage::SetupFromFile(const char* path, Vector2 size, Offset offset) {
  tex = LoadTexture(path);
  source = {0, 0, static_cast<float>(tex.width),
            static_cast<float>(tex.height)};
  dest = {0, 0, size.x, size.y};
  HandleOffset(offset);
}
void MyImage::SetupFromAtlas(Texture2D atlas, Rectangle sourceRect, Vector2 size, Offset offset) {
    tex = atlas;           // Use the provided texture atlas
    source = sourceRect;   // Set the part of the atlas to use
    dest = { 0, 0, size.x, size.y }; // Size to render it at (can be different from source size)
    HandleOffset(offset);  // Apply any positional offset
}

void MyImage::HandleOffset(Offset offset)
{
    switch (offset) {
    case Offset::Center:
        origin = { dest.width * 0.5f, dest.height * 0.5f };
        break;
    case Offset::TopLeft:
        origin = { 0, 0 };
        break;
    case Offset::TopRight:
        origin = { dest.width, 0 };
        break;
    case Offset::DownLeft:
        origin = { 0, dest.height };
        break;
    case Offset::DownRight:
        origin = { dest.width, dest.height };
        break;
    case Offset::DownCenter:
        origin = { dest.width * 0.5f, dest.height };
        break;
    case Offset::BackGround:
        break;
    default:
        break;
    }
}

void MyImage::TearDown() { UnloadTexture(tex); }

void MyImage::Draw(Vector2 position, float rotation) {
  dest.x = position.x;
  dest.y = position.y;
  DrawTexturePro(tex, source, dest, origin, rotation, WHITE);
}