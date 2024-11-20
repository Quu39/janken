#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

// ���N���X game �̒�`
class game {
public:
    virtual void select() = 0; // �������z�֐�
    virtual void introduce() = 0; // �������z�֐�
    virtual ~game() {} // ���z�f�X�g���N�^
};

// 2�l����񂯂�N���X�̒�`
class jyanken : public game {
public:
    jyanken() {}
    virtual void select() {
        int playerChoice, computerChoice;
        system("cls");
        srand((unsigned int)time(NULL));
        cout << "����񂯂�(2�l)���J�n���܂��B" << "\n";
        computerChoice = rand() % 3 + 1;
        cout << "���Ȃ����o�������͂��Ă��������B(1:�O�[ 2:�`���L 3:�p�[): ";
        cin >> playerChoice;

        cout << "\n�R���s���[�^�̎�: " << choiceToString(computerChoice) << "\n";
        cout << "���Ȃ��̎�: " << choiceToString(playerChoice) << "\n";

        if (playerChoice == computerChoice) {
            cout << "�������ł��B" << "\n";
        }
        else if ((playerChoice == 1 && computerChoice == 2) ||
            (playerChoice == 2 && computerChoice == 3) ||
            (playerChoice == 3 && computerChoice == 1)) {
            cout << "���Ȃ��̏����ł��I" << "\n";
        }
        else {
            cout << "�R���s���[�^�̏����ł��B" << "\n";
        }
    }

    virtual void introduce() {
        cout << "����񂯂�(2�l)��I�т܂����B" << endl;
    }

protected:
    string choiceToString(int choice) {
        switch (choice) {
        case 1: return "�O�[";
        case 2: return "�`���L";
        case 3: return "�p�[";
        default: return "�s��";
        }
    }
};

// 3�l����񂯂�N���X�̒�`
class threejyanken : public jyanken {
public:
    threejyanken() {}
    void select() override {
        int playerChoice, computer1Choice, computer2Choice;
        system("cls");
        srand((unsigned int)time(NULL));
        cout << "����񂯂�(3�l)���J�n���܂��B" << "\n";

        // �e�v���C���[�̑I��
        computer1Choice = rand() % 3 + 1;
        computer2Choice = rand() % 3 + 1;
        cout << "���Ȃ����o�������͂��Ă��������B(1:�O�[ 2:�`���L 3:�p�[): ";
        cin >> playerChoice;

        cout << "\n�R���s���[�^1�̎�: " << choiceToString(computer1Choice) << "\n";
        cout << "�R���s���[�^2�̎�: " << choiceToString(computer2Choice) << "\n";
        cout << "���Ȃ��̎�: " << choiceToString(playerChoice) << "\n";

        // ���s����
        int result = determineWinner(playerChoice, computer1Choice, computer2Choice);
        if (result == 0) {
            cout << "�������ł��B" << endl;
        }
        else if (result == 1) {
            cout << "���Ȃ��̏����ł��I" << endl;
        }
        else {
            cout << "�R���s���[�^" << result << "�̏����ł��B" << endl;
        }
    }

    void introduce() override {
        cout << "����񂯂�(3�l)��I�т܂����B" << endl;
    }

private:
    // ���Ҕ��胍�W�b�N
    int determineWinner(int p1, int p2, int p3) {
        // ���ꂼ��̏��s��Ԃ��m�F
        int winP1 = (p1 == 1 && p2 == 2 && p3 == 2) ||
            (p1 == 2 && p2 == 3 && p3 == 3) ||
            (p1 == 3 && p2 == 1 && p3 == 1);
        int winP2 = (p2 == 1 && p1 == 2 && p3 == 2) ||
            (p2 == 2 && p1 == 3 && p3 == 3) ||
            (p2 == 3 && p1 == 1 && p3 == 1);
        int winP3 = (p3 == 1 && p1 == 2 && p2 == 2) ||
            (p3 == 2 && p1 == 3 && p2 == 3) ||
            (p3 == 3 && p1 == 1 && p2 == 1);

        if (winP1) return 1; // �v���C���[1����
        if (winP2) return 2; // �v���C���[2����
        if (winP3) return 3; // �v���C���[3����
        return 0; // ������
    }
};

// ���C���֐�
int main() {
    int choice;
    game* selectedGame = nullptr;

    cout << "����񂯂�Q�[���ւ悤�����I" << endl;
    cout << "1: ����񂯂�(2�l)\n2: ����񂯂�(3�l)" << endl;
    cout << "�Q�[����I�����Ă������� (1�܂���2): ";
    cin >> choice;

    if (choice == 1) {
        selectedGame = new jyanken();
    }
    else if (choice == 2) {
        selectedGame = new threejyanken();
    }
    else {
        cout << "�����ȑI���ł��B�v���O�������I�����܂��B" << endl;
        return 0;
    }

    selectedGame->introduce();
    selectedGame->select();

    delete selectedGame;
    return 0;
}
