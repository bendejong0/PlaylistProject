#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>


using namespace std;

class Node{
private:
    string _title;
    string _artist;
    long _songId;
    
    
    
public:
    Node(string a = "", string b = "", long c= 0, Node* d = nullptr){
        _title = a;
        _artist = b;
        _songId = c;
        _next = d;
    }
    Node* _next;

    void AddSong(Node* current, string songTitle, string artistName, long songID){
        while(current-> _next != nullptr){
            current=current->_next;
        }
        Node* temp = new Node(songTitle, artistName, songID);
        current -> _next = temp;
        
    }
    void PrintSong(Node* current){
        while(current -> _next != nullptr){
            cout << current -> _title << endl;
            current = current -> _next;
        }
        cout << current -> _title << endl;
    }

    void DeleteSong(Node* current, string songTitle = "", string artistName = "", long songID = 0){
        Node* previous = current;
        while(current -> _title != songTitle || current  -> _artist != artistName ||  current  -> _songId != songID){
            previous = current;
            current = current -> _next;
        }
        if (current -> _title == songTitle || current -> _artist == artistName ||  current -> _songId == songID){
            Node* deleteThisNode = current;
            current = current -> _next;
            delete deleteThisNode;
            previous -> _next = current;
        }
    }
};


class Tree{
public:
    Node* _firstSongAddress;
    Tree* _next;
    string _playlistName;

    Tree(string playlistName = "", Tree* next = nullptr, Node* playlist = nullptr){
            _playlistName = playlistName;
            _next = next;
            _firstSongAddress = playlist;
        }

    void PrintPlaylists(Tree* current){
        while(current -> _next != nullptr){
            cout << current -> _playlistName << endl;
            current = current -> _next;
        }
        cout << current -> _playlistName << endl;
    }

    void CreateNewPlaylist(Tree* head, string newPlaylistName) {
        Tree* current = head;
        while (current->_next != nullptr) {
            current = current->_next;
        }
        Tree* newPlaylist = new Tree(newPlaylistName);
        current->_next = newPlaylist;
    }

    void DeletePlaylist(Tree* current, string playlistName){
        Tree* previous = current;
        while(current -> _playlistName != playlistName){
            previous = current;
            current = current -> _next;
        }
        if (current -> _playlistName == playlistName){
            Tree* deleteThisNode = current;
            current = current -> _next;
            delete deleteThisNode;
            previous -> _next = current;
        }
    }
};

class Menu : public Tree{
private:
    enum options {CREATE = 1, 
                  SELECT=2, 
                  DELETE=3, 
                  PRINT=4, 
                  EXIT=5};

public:

    // function that greets the user
    void Welcome(){
        cout << "-- Welcome to your playlist homepage --" << endl << endl;
    }

    // function that shows options
    void ShowOptions(){
        cout << "Would you like to: \n 1) Create a new playlist \n 2) Select a playlist \n 3) Delete a playlist \n 4) Display all playlists \n 5) Exit" << endl;
        cout << "Input the number's corresponding value: ";
    }

    // function that selects a playlist
    void SelectPlaylist(Tree* current){
        
        // a variable to count how many playlists we have.
        Tree* firstIteration = current;
        int playlistCounter=1;
        while(firstIteration -> _next != nullptr){
            cout << firstIteration -> _playlistName << endl;
            playlistCounter++;
        }
        cout << firstIteration -> _playlistName << endl;
        playlistCounter++;

        // map that keeps track of which number is associated with which playlist
        unordered_map<int, string> playlistMap;
        Tree* secondIteration = current;
        // assigning every playlist a number
        for(int i = 1; i < playlistCounter; i++){
            cout << i << ") " << secondIteration -> _playlistName << endl;
            playlistMap[i] = secondIteration -> _playlistName;
            secondIteration = secondIteration -> _next;
        }
        
        int user;
        cout << "Select what playlist you'd like to listen to: ";
        cin >> user;
        playlistMap.find(user);
        cout << endl << "Opening..."  << endl << endl;

        
        enum songOptions{
            ADD = 1,
            DELETE = 2,
            EXIT = 4
        };
        songOptions songOption;
        // this is used to select what the user wants to do to the songs in their playlist.
        int songSelectUser;
        if(current-> _firstSongAddress == nullptr){
            int addOrGoBack;
            cout << "This playlist is empty!" << endl;
            cout << " 1) Add a song\n 2) Go back" << endl;
            cout << "Input your option's corresponding number: ";
            cin >> addOrGoBack;


            if(addOrGoBack == 1){
                string songTitle;
                string artistName;
                long songID;
                cout << "Enter the song's title: ";
                getline(cin, songTitle);
                cin.ignore();
                cout << "Enter the artist's name: ";
                getline(cin, artistName);
                cin.ignore();
                cout << "Enter the song's ID: ";
                cin >> songID;
                Node* temp = new Node(songTitle, artistName, songID);
                current -> _firstSongAddress = temp;
            }
            else if(addOrGoBack == 2){
                return;
            }
            else{
                cout << "Please enter a valid option!" << endl;
            }
        }
        
        else if(current-> _firstSongAddress!=nullptr){
            // the firstSong node basically functions as the head node.
            Node* firstSong = current -> _firstSongAddress;
            Node* temp = firstSong;
            // creating a loop so the user can manipulate the desired playlist.
            bool falseIfExitLoop = true;
            while(falseIfExitLoop){
                cout << "What would you like to do?\n 1) Add a song\n 2) Delete a song\n 4) Go back" << endl;
                cin >> songSelectUser;
                songOption = static_cast<songOptions>(songSelectUser);
                switch(songOption){
                    case ADD:
                        // TODO: FIX THIS!!
                        break;

                    case DELETE:
                        // TODO: FIX THIS ASWELL!!
                        break;

                    case EXIT:
                        cout << "Exiting..." << endl;
                        falseIfExitLoop = false;
                        break;

                    default:
                        cout << "Please enter a valid option!" << endl;
                        break;

                }
            }
        }
    }

    // function that processes user input
    int ProcessInput(Tree* head) {
        string plName;
        int user;
        cin >> user;
        options optionlist = static_cast<options>(user);
        Tree tree;

        //a big important switch that processes user inputs
        switch (optionlist) {

            case CREATE:
                cout << "Name your playlist: ";
                cin.ignore();
                getline(cin, plName);
                while (head->_next != nullptr) {
                    head = head->_next;
                }
                // clear the buffer.
                head->Tree::CreateNewPlaylist(head, plName);
                return 0;


            case SELECT:
                cout << endl;
                Menu::SelectPlaylist(head);
                cout << endl << endl;
                return 0;
            

            case PRINT:
                cout << "All playlists: " << endl << endl;
                Tree::PrintPlaylists(head);
                cout << endl << endl;
                return 0;
            
            // if the user wants to delete a playlist,
            case DELETE:
                cout << "Which playlist would you like to delete?" << endl;
                Tree::PrintPlaylists(head);
                cin.ignore();
                getline(cin, plName); // we get the playlist name,
                Tree::DeletePlaylist(head, plName); // and run the delete function.
                return 0;

            // if the user wants to exit the program we simply return 5. this breaks our while loop in main.
            case EXIT:
                cout << "Goodbye!" << endl;
                return 5;

            // if the user inputs an invalid option, we tell them to try again.
            default:
                cout << "Please choose a valid option!" << endl;
                return 0;
        }
        // incase the user (somehow) gets past our switch statement without triggering the default statement
        // we return 1 which throws an error.
        return 1;
    }
};

int main()
{
    Menu menu;
    
    menu.Welcome();
    cout << "Press 1 to create a playlist" << endl;

    // this is used to create the first playlist, then never again.
    
    string plName;
    int user;
    cin >> user;

    Tree* head;
        
    if (user == 1) {
        cout << "Name your playlist: ";
        cin.ignore(); // Clear the newline character from the buffer
        getline(cin, plName);
        head = new Tree(plName); // Use the existing 'head' pointer
    } 
    else {
       while (true) {
            cout << "Please choose a valid option!" << endl;
            cout << "Press 1 to create your first playlist" << endl;
            cin >> user;
            if (user == 1) {
                break;
            }
        }
    }
    
    while(true){
        
        cout << endl;
        menu.Welcome();
        menu.ShowOptions();
        user = menu.ProcessInput(head);

        if(user == 5){
            break;
        }
        if(user == 1){
            cout << "ERROR on ProcessInput" << endl;
        }
    }

    return 0;
}
