#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// 基底クラス game の定義
class game {
public:
    virtual void select() = 0; // 純粋仮想関数
    virtual void introduce() = 0; // 純粋仮想関数
    virtual ~game() {} // 仮想デストラクタ
};

// 2人じゃんけんクラスの定義
class jyanken : public game {
public:
    jyanken() {}
    virtual void select() {
        int playerChoice, computerChoice;
        system("cls");
        srand((unsigned int)time(NULL));
        cout << "じゃんけん(2人)を開始します。" << "\n";
        computerChoice = rand() % 3 + 1;
        cout << "あなたが出す手を入力してください。(1:グー 2:チョキ 3:パー): ";
        cin >> playerChoice;

        cout << "\nコンピュータの手: " << choiceToString(computerChoice) << "\n";
        cout << "あなたの手: " << choiceToString(playerChoice) << "\n";

        if (playerChoice == computerChoice) {
            cout << "あいこです。" << "\n";
        }
        else if ((playerChoice == 1 && computerChoice == 2) ||
            (playerChoice == 2 && computerChoice == 3) ||
            (playerChoice == 3 && computerChoice == 1)) {
            cout << "あなたの勝ちです！" << "\n";
        }
        else {
            cout << "コンピュータの勝ちです。" << "\n";
        }
    }

    virtual void introduce() {
        cout << "じゃんけん(2人)を選びました。" << endl;
    }

protected:
    string choiceToString(int choice) {
        switch (choice) {
        case 1: return "グー";
        case 2: return "チョキ";
        case 3: return "パー";
        default: return "不明";
        }
    }
};

// 3人じゃんけんクラスの定義
class threejyanken : public jyanken {
public:
    threejyanken() {}
    void select() override {
        int playerChoice, computer1Choice, computer2Choice;
        system("cls");
        srand((unsigned int)time(NULL));
        cout << "じゃんけん(3人)を開始します。" << "\n";

        // 各プレイヤーの選択
        computer1Choice = rand() % 3 + 1;
        computer2Choice = rand() % 3 + 1;
        cout << "あなたが出す手を入力してください。(1:グー 2:チョキ 3:パー): ";
        cin >> playerChoice;

        cout << "\nコンピュータ1の手: " << choiceToString(computer1Choice) << "\n";
        cout << "コンピュータ2の手: " << choiceToString(computer2Choice) << "\n";
        cout << "あなたの手: " << choiceToString(playerChoice) << "\n";

        // 勝敗判定
        int result = determineWinner(playerChoice, computer1Choice, computer2Choice);
        if (result == 0) {
            cout << "あいこです。" << endl;
        }
        else if (result == 1) {
            cout << "あなたの勝ちです！" << endl;
        }
        else {
            cout << "コンピュータ" << result << "の勝ちです。" << endl;
        }
    }

    void introduce() override {
        cout << "じゃんけん(3人)を選びました。" << endl;
    }

private:
    // 勝者判定ロジック
    int determineWinner(int p1, int p2, int p3) {
        // それぞれの勝敗状態を確認
        int winP1 = (p1 == 1 && p2 == 2 && p3 == 2) ||
            (p1 == 2 && p2 == 3 && p3 == 3) ||
            (p1 == 3 && p2 == 1 && p3 == 1);
        int winP2 = (p2 == 1 && p1 == 2 && p3 == 2) ||
            (p2 == 2 && p1 == 3 && p3 == 3) ||
            (p2 == 3 && p1 == 1 && p3 == 1);
        int winP3 = (p3 == 1 && p1 == 2 && p2 == 2) ||
            (p3 == 2 && p1 == 3 && p2 == 3) ||
            (p3 == 3 && p1 == 1 && p2 == 1);

        if (winP1) return 1; // プレイヤー1勝ち
        if (winP2) return 2; // プレイヤー2勝ち
        if (winP3) return 3; // プレイヤー3勝ち
        return 0; // あいこ
    }
};

// メイン関数
int main() {
    int choice;
    game* selectedGame = nullptr;

    cout << "じゃんけんゲームへようこそ！" << endl;
    cout << "1: じゃんけん(2人)\n2: じゃんけん(3人)" << endl;
    cout << "ゲームを選択してください (1または2): ";
    cin >> choice;

    if (choice == 1) {
        selectedGame = new jyanken();
    }
    else if (choice == 2) {
        selectedGame = new threejyanken();
    }
    else {
        cout << "無効な選択です。プログラムを終了します。" << endl;
        return 0;
    }

    selectedGame->introduce();
    selectedGame->select();

    delete selectedGame;
    return 0;
}
