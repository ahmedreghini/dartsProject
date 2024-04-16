#include<iostream> //for std c++
#include<fstream> //for file management
#include<sstream> //for string stream
#include<string> //for strings

using namespace std;
fstream file;
string 
firstPName = "Guest1", 
secondPName= "Guest2", 
matchTitle= "Dart Mutch",
buffer="", 
firstPBuffer="", 
secondPBuffer="";

int 
firstPScore=501, //first player score
secondPScore=501, //second player score
someOfDarts=0, //some of darts of every player 3 shot
ruleFirstTo=5, //rule first to (max of legs)
playFirstLeg=0, //who play first
playFirst=0,
leg=1, //number of leg (first leg, second leg...)
firstPLegWin=0, //legs wins by first player
secondPLegWin=0; //legs wins by second player

void newLeg(string& pNameFirstGameOn) {
        firstPScore = 501;
        secondPScore = 501;
        cout << "----------Leg " << leg << "-----------\n";
        cout << "Leg " << leg << " " << pNameFirstGameOn << " is first game on.\n";
        cout << firstPName << " score is " << firstPScore << endl;
        cout << secondPName << " score is " << secondPScore << endl;

        buffer = "---------Leg " + to_string(leg) + "----------- (";
        buffer += to_string(firstPLegWin) + " , " + to_string(secondPLegWin) + ")\n";
        buffer += "Leg " + to_string(leg) + " " + pNameFirstGameOn + " is first game on.\n\n";
}

void PSome(string& pName, int& pScore, int& pLegWin, string& pBuffer)
{
    if(leg==1 && firstPScore==501 && secondPScore==501) 
    {
        buffer += "---------Leg " + to_string(leg) + "----------- (" + to_string(firstPLegWin) + " , " + to_string(secondPLegWin);
        buffer += ")\nLeg " + to_string(leg) + " " + pName + " is first game on.\n\n";
    }
    
    cout << "some of darts of " << pName << " is: ";
    cin >> someOfDarts;
    cin.ignore(1000,'\n');
    if((pScore-someOfDarts) > 0 && (pScore-someOfDarts)  != 1)
    {
        pBuffer += to_string(pScore) + "-" + to_string(someOfDarts) + "=";
        pScore -= someOfDarts;
        pBuffer += to_string(pScore) + "\n";
        cout << pName << " score is " << pScore << endl;
    }
    else if ((pScore-someOfDarts) == 1 || (pScore-someOfDarts) < 0)
    {
        pBuffer += "No score \n";
        cout << "No score " << endl;
        cout << pName << " score is " << pScore << endl;
    }
    else if ((pScore-someOfDarts) == 0)
    {
        int x = 1;
        cout << "Please enter the nuber if darts to finish: ";
        cin >> x;
        cin.ignore(1000, '\n');
        pBuffer += "X" + to_string(x) + "\n";

        pLegWin += 1;
        cout << "Game shot " <<"Leg " << leg << " " << pName << ".\n";

        buffer += firstPBuffer + secondPBuffer;
        if (pLegWin < ruleFirstTo)
        {
            buffer += "\nGame shot Leg " + to_string(leg) + " " + pName + ".\n\n";
            firstPBuffer = "\n---" + firstPName + "---\n";
            secondPBuffer = "\n---" + secondPName + "---\n";
        }

        //add Leg to file.
        file.open(matchTitle,ios::app);
        file << buffer;
        if(!file) { cout<<"Error in creating file!!!";} 
        file.close();
        
        leg += 1;
        if (playFirstLeg == 1)
        {
            if (leg &1) {playFirst = 1; newLeg(firstPName);}
            else {playFirst = 2; newLeg(secondPName);}
        }
        else if (playFirstLeg == 2)
        {
            if (leg &1) {playFirst = 2; newLeg(secondPName);}
            else {playFirst = 1; newLeg(firstPName);}
        }
    }
}

void startPlay()
{
    playFirst = playFirstLeg;
    
    while (ruleFirstTo != firstPLegWin && ruleFirstTo != secondPLegWin)
    {
        if(playFirst==1) 
        {
            playFirst=2;
            PSome(firstPName, firstPScore, firstPLegWin, firstPBuffer);
        } 
        else if (playFirst==2)
        {
            playFirst=1;
            PSome(secondPName, secondPScore, secondPLegWin, secondPBuffer);
        } 
        else 
        {
            cout << "you write wrong play first!";
        }
    }
    
    if(ruleFirstTo == firstPLegWin) 
    {
        cout << "Game shot and match " << firstPName << "\n";
        buffer = "\nGame shot and match " + firstPName + "\n";
    }
    if(ruleFirstTo == secondPLegWin) 
    {
        cout << "Game shot and match " << secondPName << "\n";
        buffer = "\nGame shot and match " + secondPName + "\n";
    }

    file.open(matchTitle,ios::app);
    file << buffer;
    if(!file) { cout<<"Error in creating file!!!";} 
    file.close();
}

void matchInitialisation() 
{
    string fName, sName;

//The title of the match
    cout << "Please enter the mutch title: ";
    getline(cin, matchTitle);
    buffer += matchTitle + "\n\n";
    
    matchTitle += ".txt";
    cout << "\n";

//The Rule of the match First to ?
    cout << "Please enter the Rule First to: ";
    cin >> ruleFirstTo;
    cin.ignore(1000, '\n');
    cout << "\n";
    buffer += "Rule: First to " + to_string(ruleFirstTo) + "\n\n";

//What are the players names?
    //first player name
    cout << "please enter first player name: \n";
    getline(cin, fName);
    if(fName != "") firstPName = fName;
    cout << "\n";
    firstPBuffer += "\n---" + firstPName + "---\n";

    //second player name
    cout << "please enter second player name: \n";
    getline(cin, secondPName);
    if(sName != "") secondPName = sName;
    cout << "\n";
    secondPBuffer += "\n---" + secondPName + "---\n";

//Who plays First LEG?
    cout << "Who plays first? \n";
    cout << "If " << firstPName << " type 1, If " << secondPName << " type 2:\n";
    cin >> playFirstLeg;
    cin.ignore(1000, '\n');
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    matchInitialisation();
    startPlay();
    
    return 0;
}
