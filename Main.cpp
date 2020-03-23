#include <Siv3D.hpp>  // OpenSiv3D v0.4.2
#include "Common.h"
#include "TestScene.h"
#include "Title.h"
#include "Config.h"
using namespace com;
//using App = SceneManager<String>;

void Main() {
    Scene::SetBackground(Palette::Black);
    Window::Resize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
    Scene::Resize(DEFAULT_SCENE_WIDTH, DEFAULT_SCENE_HEIGHT);

    // シーンの登録
    App manager;
    manager.add<Title>(U"Title");
    manager.add<TestScene>(U"TestScene");
    manager.add<Config>(U"Config");

    // アッセットの登録
    TextureAsset::Register(U"MapChip1", U"../Asset/chip1.png");
    TextureAsset::Register(U"MapChip2", U"../Asset/chip2.png");
    TextureAsset::Register(U"Roomba", U"../Asset/roomba.png");

    while (System::Update()) {
        if (!manager.update()) {
            break;
        }
        //int xRatio = 16;
        //int yRatio = 9;


        // 20 × 15
        /*constexpr int xRatio = DEFAULT_WINDOW_HEIGHT / BLOCK_SIZE;
        constexpr int yRatio = 480;
        constexpr int blockSize = 32;

        for (int i = 0; i < xRatio / blockSize; i++) {
          for (int j = 0; j < yRatio / blockSize; j++) {
            if (j % 2 != i %2) {
             Rect(Point(blockSize * i, blockSize * j)
               , blockSize).draw(Palette::Red);
            }
          }
        }*/

    }
}

//
// = アドバイス =
// Debug ビルドではプログラムの最適化がオフになります。
// 実行速度が遅いと感じた場合は Release ビルドを試しましょう。
// アプリをリリースするときにも、Release ビルドにするのを忘れないように！
//
// 思ったように動作しない場合は「デバッグの開始」でプログラムを実行すると、
// 出力ウィンドウに詳細なログが表示されるので、エラーの原因を見つけやすくなります。
//
// = お役立ちリンク =
//
// OpenSiv3D リファレンス
// https://siv3d.github.io/ja-jp/
//
// チュートリアル
// https://siv3d.github.io/ja-jp/tutorial/basic/
//
// よくある間違い
// https://siv3d.github.io/ja-jp/articles/mistakes/
//
// サポートについて
// https://siv3d.github.io/ja-jp/support/support/
//
// Siv3D Slack (ユーザコミュニティ) への参加
// https://siv3d.github.io/ja-jp/community/community/
//
// 新機能の提案やバグの報告
// https://github.com/Siv3D/OpenSiv3D/issues
//
