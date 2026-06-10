#pragma once


//様々な情報を格納するクラス
//シングルトンにしてどこでも持ってこれるようにする
class Info
{
public:

	Info() {};
	~Info() {};

	void Init();

	//ゲッター========

	int GetScore() { return m_Score; }

	int GetCoin() { return m_Coin; }

	int GetRunDistance() { return m_RunDistance; }

	//セッター

	//引数の数字を現在のスコアに足す
	void SetScore(int _score) { m_Score += _score; }

	void SetCoin(int _coin) { m_Coin += _coin; }

	void SetRunDistance() { m_RunDistance += 1; }

private:

	//ゲームシーンの所持スコア
	int m_Score;

	//ゲームシーンの所持コイン
	int m_Coin;

	//ゲームシーンの走った距離
	int m_RunDistance;

	//音関係のファイルを読み込む予定=====


public:

	//シングルトン
	static Info& Instance()
	{
		static Info instance;
		return instance;
	}
};
