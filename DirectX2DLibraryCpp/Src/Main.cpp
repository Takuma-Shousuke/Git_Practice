#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <crtdbg.h>
#include <Windows.h>
#include "Engine/Engine.h"
#include "Common/Vec.h"

Vec2 g_Position = Vec2(0.0f, 0.0f);
Vec2 g_Scale = Vec2(1.0f, 1.0f);
float g_Angle = 0.0f;

// ゲーム処理
void GameProcessing();
// 描画処理
void DrawProcessing();

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmpLine,
	_In_ INT       nCmdShow)
{
	// エンジンの初期化
	// ゲームループ開始前に1度だけ実行する
	if (Engine::Initialize(640, 480, "Sample") == false)
	{
		return 0;
	}

	//画像ファイルの呼び出し
	bool is_success = Engine::LoadTexture("グー", "Res/rock.jpg");
					  Engine::LoadTexture("チョキ", "Res/scisors.png");
					  Engine::LoadTexture("パー", "Res/paper.jpg");

					  
	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			// ゲーム処理
			GameProcessing();

			// 描画開始
			DrawProcessing();
		}
	}

	// エンジン終了
	// ゲームループ終了後に1度だけ実行する
	// テクスチャとサウンドファイルも全て解放する
	Engine::Release();

	// メモリリーク検出
	_CrtDumpMemoryLeaks();

	return 0;
}
void GameProcessing()
{
	// 入力データの更新
	Engine::Update();


	//========================================================
	// キーボードの入力取得
	//========================================================

	//if (Engine::IsKeyboardKeyPushed(DIK_SPACE) == true)
	//{
	//	// キーが押された瞬間の処理
	//}

	//if (Engine::IsKeyboardKeyHeld(DIK_LEFT) == true)
	//{
	//	// キーが押されている間の処理
	//}

	//if (Engine::IsKeyboardKeyReleased(DIK_A))
	//{
	//	// キーが離された瞬間の処理
	//}
}

void DrawProcessing()
{
	// 描画開始
	// 描画処理を実行する場合、必ず最初実行する
	Engine::StartDrawing(0);

	// フォント描画
	Engine::DrawTexture(0, 0, "グー",  255, 0.0f, 0.5f, 0.5f);
	Engine::DrawTexture(0, 0, "チョキ",255, 0.0f, 0.5f, 0.5f);
	Engine::DrawTexture(0, 0, "パー",  255, 0.0f, 0.5f, 0.5f);


	// 描画終了
	// 描画処理を終了する場合、必ず最後に実行する
	Engine::FinishDrawing();
}

void Janken()
{
	//・プレイヤーの出す手の情報を入れておく変数
	int player = -1;  //プレイヤーが出した手を入れておく
	int CPU;     //コンピューターが出した手を入れておく

	Engine::DrawFont(0.0f, 0.0f, "じゃんけんをしましょう\n", FontSize::Small, FontColor::White);
	Engine::DrawFont(0.1f, 0.1f, "0 :   グー\n", FontSize::Small, FontColor::White);
	Engine::DrawFont(0.2f, 0.2f, "1 : チョキ\n", FontSize::Small, FontColor::White);
	Engine::DrawFont(0.3f, 0.3f, "2 : 　パー\n", FontSize::Small, FontColor::White);
	Engine::DrawFont(0.4f, 0.4f, "			\n", FontSize::Small, FontColor::White);
	Engine::DrawFont(0.5f, 0.5f, "出したい手を上から選択してください", FontSize::Small, FontColor::White);

	//・コンピューターがランダムで、手を変える仕組み
	srand((unsigned)time(NULL));//乱数の初期化 = srand
	//乱数の初期化(現在時刻をseed値とする)
	CPU = rand() % 3;
	//3で余りをとることで、必ず0∼2の値になる->0,1,2を3で割る。そしてその余り。

	if (Engine::IsKeyboardKeyPushed(DIK_0) == true)
	{
		player = 0;
	}
	else if (Engine::IsKeyboardKeyPushed(DIK_1) == true)
	{
		player = 1;
	}
	else if(Engine::IsKeyboardKeyPushed(DIK_2) == true)
	{
		player = 2;
	}

	

	//・プレイヤーとコンピューターの手を比較して、勝ち負けを表示する仕組み
	Engine::DrawFont(0.0f, 0.0f,"\n\n", FontSize::Small, FontColor::White);

	if (player == 0)
	{
		Engine::DrawFont(0.4f, 0.4f, " プレイヤー : グー \n", FontSize::Small, FontColor::White);
	}
	else if (player == 1)
	{
		Engine::DrawFont(0.4f, 0.4f, " プレイヤー : チョキ \n", FontSize::Small, FontColor::White);
	}
	else if (player == 2)
	{
		Engine::DrawFont(0.4f, 0.4f, " プレイヤー ; パー \n", FontSize::Small, FontColor::White);
	}
	if (CPU == 0)
	{
		Engine::DrawFont(0.4f, 0.4f, "コンピューター : グー\n", FontSize::Small, FontColor::White);
	}
	else if (CPU == 1)
	{
		Engine::DrawFont(0.4f, 0.4f, " コンピューター : チョキ\n", FontSize::Small, FontColor::White);
	}
	else if (CPU == 2)
	{
		Engine::DrawFont(0.4f, 0.4f, " コンピューター ; パー\n", FontSize::Small, FontColor::White);
	}
	//お互いの手を比較して、結果を表示する
	if (player == CPU)
	{
		Engine::DrawFont(0.4f, 0.4f, " 結果 : あいこ\n", FontSize::Small, FontColor::White);
	}
	else if (player == 0)	//プレイヤーがグー
	{
		//一番上で同じ値かどうかを比較しているため、
		//ここには必ず違う値が入ってくる
	}
	if (CPU == 2)	//コンピューターがパー
	{
		Engine::DrawFont(0.4f, 0.4f, " 結果 : コンピューターの勝ち\n", FontSize::Small, FontColor::White);
	}
	else if(CPU ==1)
	{
		Engine::DrawFont(0.4f, 0.4f, " 結果 : プレイヤーの勝ち\n", FontSize::Small, FontColor::White);
	}
	//残りの判定を書いて、ゲームを完成させよう！	
	else if (player == 1)	//プレイヤーがチョキ
	{
		if (CPU == 0)	//コンピューターがグー
		{
			Engine::DrawFont(0.4f, 0.4f, " 結果 : コンピューターの勝ち\n", FontSize::Small, FontColor::White);
		}
		else if(CPU ==2)
		{
			Engine::DrawFont(0.4f, 0.4f, " 結果 : プレイヤーの勝ち\n", FontSize::Small, FontColor::White);
		}
	}
	else if (player == 2)	//プレイヤーがパー
	{
		if (CPU == 1)	//コンピューターがチョキ
		{
			Engine::DrawFont(0.4f, 0.4f, " 結果 : コンピューターの勝ち\n", FontSize::Small, FontColor::White);
		}
		else if(CPU == 0)
		{
			Engine::DrawFont(0.4f, 0.4f, " 結果 : プレイヤーの勝ち\n", FontSize::Small, FontColor::White);
		}
	}
}