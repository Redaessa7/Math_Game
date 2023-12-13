/* --------------------------------------------
    Name Project: Math Game
    NumOfProject: 2
    data: 12/11/2023
    dev Name: Reda Essa
    tec-tools : Functional Programming, Structures, Arrays , Enums.
-----------------------------------------------*/
#include <iostream>
#include <cstdlib>
using namespace std;

enum enQuestionsLevel
{
    Easy = 1,
    Med = 2,
    Hard = 3,
    QMix = 4
};
enum enOpTypes
{
    Add = 1,
    Sub = 2,
    Multiply = 3,
    Division = 4,
    Mix = 5
};
enum enQuestionResult
{
    WrongAnswer = 0,
    CorrectAnswer = 1
};
enum enFinalGameResult
{
    Fail = 0,
    Pass = 1
};

struct stQuestion
{
    short NumOfQuestion;
    short FirstOperand;
    short SecondOperand;
    short userAnswer;
    enOpTypes OpType;
    short correctAnswer;
    enQuestionResult QuestionResult;
};
struct stFinalResult
{
    short NumOfQuestions;
    enQuestionsLevel QuestionsLevel;
    enOpTypes OpType;
    short NumOfRightAnswer;
    short NumOfWrongAnswer;
    enFinalGameResult FinalResult;
};

short ReadNumber(string msg)
{
    short num = 0;
    cout << msg + " ";
    cin >> num;
    return num;
}

short HowManyQuestions()
{
    short PositiveNum = 0;
    do
    {
        PositiveNum = ReadNumber("How Many Questions Do You Want Answer?");
    } while (PositiveNum <= 0);
    return PositiveNum;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short QLevel = 0;
    do
    {
        QLevel = ReadNumber("Plz Enter Questions Level [1]: Easy, [2]: Med, [3]: Hard, [4]: Mix ?");
    } while (QLevel <= 0 || QLevel > 4);
    return (enQuestionsLevel)QLevel;
}

enOpTypes ReadOperationType()
{
    short opType = 0;
    do
    {
        opType = ReadNumber("Plz Enter Operation Type [1]: Add, [2]: Sub, [3]: Mult, [4]: Div, [5]: Mix ?");
    } while (opType <= 0 || opType > 5);
    return (enOpTypes)opType;
}

int random(int from, int to)
{
    int randNum = rand() % (to - from + 1) + from; // ranged from num to num ;
    return randNum;
}

short GenerateNumBaseOnLevel(enQuestionsLevel QuestionLevel)
{
    short num = 0;
    switch (QuestionLevel)
    {
    case enQuestionsLevel::Easy:
        num = random(1, 10);
        break;
    case enQuestionsLevel::Med:
        num = random(20, 50);
        break;
    case enQuestionsLevel::Hard:
        num = random(50, 100);
        break;
    default:
        num = random(1, 100);
        break;
    }
    return num;
}

enOpTypes RandomOperationType()
{
    return (enOpTypes)random(1, 4);
}

char symbolOpTypes(enOpTypes opType)
{
    switch (opType)
    {
    case enOpTypes::Add:
        return '+';
    case enOpTypes::Sub:
        return '-';
    case enOpTypes::Multiply:
        return '*';
    case enOpTypes::Division:
        return '/';
    default:
        return 'M';
    }
}

string SymbolQuestionLevel(enQuestionsLevel QLevel)
{
    switch (QLevel)
    {
    case enQuestionsLevel::Easy:
        return "Easy";
    case enQuestionsLevel::Med:
        return "Med";
    case enQuestionsLevel::Hard:
        return "Hard";
    default:
        return "Mix";
    }
}

short Calculator(stQuestion Question)
{
    switch (Question.OpType)
    {
    case enOpTypes::Add:
        return Question.FirstOperand + Question.SecondOperand;
    case enOpTypes::Sub:
        return Question.FirstOperand - Question.SecondOperand;
    case enOpTypes::Multiply:
        return Question.FirstOperand * Question.SecondOperand;
    case enOpTypes::Division:
        return Question.FirstOperand / Question.SecondOperand;
    default:
        return Question.FirstOperand + Question.SecondOperand;
    }
}

enQuestionResult CheckUserAnswer(short userAnswer, short CorrectAnswer)
{
    if (userAnswer == CorrectAnswer)
        return enQuestionResult::CorrectAnswer;
    else
        return enQuestionResult::WrongAnswer;
}

string resultUserAnswer(enQuestionResult QResult)
{
    string arrResult[] = {"Wrong Answer", "Correct Answer"};
    return arrResult[0 + (short)QResult];
}

enFinalGameResult CheckFinalResult(short userCorrectAnswers, short userWrongAnswers)
{
    if (userCorrectAnswers > userWrongAnswers)
        return enFinalGameResult::Pass;
    else
        return enFinalGameResult::Fail;
}

bool ExitGame()
{
    char exit;
    cout << "Do You Want play Again? Y/N? ";
    cin >> exit;

    if (exit == 'Y' || exit == 'y')
        return true;
    else
        return false;
}

void ResetScreen()
{
    system("cls");
    system("color 0f");
}

void ChangeScreenColor(enQuestionResult QuestionResult)
{
    switch (QuestionResult)
    {
    case enQuestionResult::CorrectAnswer:
        cout << "\a";
        system("color 2f");
        break;
    default:
        cout << "\a";
        system("color 4f");
        break;
    }
}

void PrintTitleFinalScreen(stFinalResult finalGameResult)
{
    cout << "\n\n------------------------------------------------------\n";
    cout << "               Final Result Is ";

    if (finalGameResult.FinalResult == enFinalGameResult::Pass)
    {
        cout << "Pass :)";
        ChangeScreenColor((enQuestionResult)enFinalGameResult::Pass);
    }
    else
    {
        cout << "Fail :(";
        ChangeScreenColor((enQuestionResult)enFinalGameResult::Fail);
    }

    cout << "               \n";
    cout << "------------------------------------------------------\n";
}

void PrintFinalResultScreen(stFinalResult finalGameResult)
{
    cout << "\nNumber Of Questions    : " << finalGameResult.NumOfQuestions << endl;
    cout << "Questions Level          : " << SymbolQuestionLevel(finalGameResult.QuestionsLevel) << endl;
    cout << "Operation Type           : " << symbolOpTypes(finalGameResult.OpType) << endl;
    cout << "Number Of Right Answer   : " << finalGameResult.NumOfRightAnswer << endl;
    cout << "Number Of Wrong Answer   : " << finalGameResult.NumOfWrongAnswer << endl;
    cout << "----------------------------------------------------------------\n";
}

void PrintQuestion(stQuestion Question, short numOfQuestions)
{
    cout << "\nQuestion [" << Question.NumOfQuestion << "/" << numOfQuestions << "]\n\n";
    cout << Question.FirstOperand << endl;
    cout << symbolOpTypes(Question.OpType) << endl;
    cout << Question.SecondOperand << endl;
    cout << "-----------------" << endl;
}

void PrintQuestionResult(stQuestion Question, short &NumOfRightAnswer, short &NumOfWrongAnswer)
{
    if (Question.QuestionResult == enQuestionResult::WrongAnswer)
    {
        cout << "\n" + resultUserAnswer(Question.QuestionResult) << endl;
        cout << "The Correct Answer Is: " << Question.correctAnswer << endl;
        ChangeScreenColor(Question.QuestionResult);
        NumOfWrongAnswer++;
    }
    else
    {
        cout << "\n" + resultUserAnswer(Question.QuestionResult) << endl;
        ChangeScreenColor(Question.QuestionResult);
        NumOfRightAnswer++;
    }
}

stFinalResult FillFinalGameResult(short numOfQuestion, enQuestionsLevel QLevel, enOpTypes opTypeMain, short NumOfRightAnswer, short NumOfWrongAnswer)
{
    stFinalResult finalGameResult;
    finalGameResult.NumOfQuestions = numOfQuestion;
    finalGameResult.QuestionsLevel = QLevel;
    finalGameResult.OpType = opTypeMain;
    finalGameResult.NumOfRightAnswer = NumOfRightAnswer;
    finalGameResult.NumOfWrongAnswer = NumOfWrongAnswer;
    finalGameResult.FinalResult = CheckFinalResult(NumOfRightAnswer, NumOfWrongAnswer);
    return finalGameResult;
}

stFinalResult PlayGame()
{
    stQuestion Question;

    short numOfQuestion = HowManyQuestions();
    enQuestionsLevel QLevel = ReadQuestionsLevel();
    enOpTypes opTypeMain = ReadOperationType();
    Question.OpType = opTypeMain;

    short NumOfRightAnswer = 0, NumOfWrongAnswer = 0;

    for (short NumQuestion = 1; NumQuestion <= numOfQuestion; NumQuestion++)
    {
        Question.NumOfQuestion = NumQuestion;
        Question.FirstOperand = GenerateNumBaseOnLevel(QLevel);
        Question.SecondOperand = GenerateNumBaseOnLevel(QLevel);
        Question.correctAnswer = Calculator(Question);

        if (opTypeMain == enOpTypes::Mix)
        {
            Question.OpType = RandomOperationType();
        }

        PrintQuestion(Question, numOfQuestion);
        Question.userAnswer = ReadNumber("");
        Question.QuestionResult = CheckUserAnswer(Question.userAnswer, Question.correctAnswer);
        PrintQuestionResult(Question, NumOfRightAnswer, NumOfWrongAnswer);
    }
    return FillFinalGameResult(numOfQuestion, QLevel, opTypeMain, NumOfRightAnswer, NumOfWrongAnswer);
}

void StartGame()
{
    do
    {
        ResetScreen();
        stFinalResult finalGameResult = PlayGame();
        PrintTitleFinalScreen(finalGameResult);
        PrintFinalResultScreen(finalGameResult);
    } while (ExitGame());
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}