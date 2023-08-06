#include <iostream>
#include <string>
#include <iomanip>


using namespace std;

class Node{
private:
    string _title;
    string _artist;
    long _songId;
    
    Node(string a = "", string b = "", long c= 0, Node* d = nullptr){
        _title = a;
        _artist = b;
        _songId = c;
        _next = d;
    }
    
public:
    Node* _next;

    void addSong(Node* current, string songTitle, string artistName, long songID){
        while(current-> _next != nullptr){
            current=current->_next;
        }
        Node* temp = new Node(songTitle, artistName, songID);
        current -> _next = temp;
        
    }
    void printsong(Node* current){
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


// just in case
class Tree{
private:
    string _playlistName;
    Node* _playlistAddress;

public:
    Tree* _next;

    Tree(string playlistName = "", Tree* next = nullptr, Node* playlist = nullptr){
            _playlistName = playlistName;
            _next = next;
            _playlistAddress = playlist;
        }

    void PrintPlaylists(Tree* current){

        while(current -> _next != nullptr){
            cout << current -> _playlistName << endl;
        }
        cout << current -> _playlistName << endl;
    }

    void CreateNewPlaylist(string newPlaylistName) {
        Tree* current = this;
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
    enum options {CREATE = 1, SELECT, DELETE, PRINT, EXIT};

public:

    // function that greets the user
    void Welcome(){
        cout << "-- Welcome to your playlist homepage --" << endl << endl;
    }

    // function that shows options
    void ShowOptions(){
        cout << "Would you like to: \n 1) Create a new playlist \n 2) Select a playlist \n 3) Delete a playlist \n 4) Display all playlists \n 5) Exit" << endl;
        cout << "Input the number's corresponding value:";
    }

    // function that selects a playlist
    void SelectPlaylist(){
        cout << "Select what playlist you'd like to listen to: " << endl << endl;
    }

    // function that processes user input
    void ProcessInput(Tree* head) {
        string plName;
        int user;
        cin >> user;
        options optionlist = static_cast<options>(user);
        Tree tree;

        while (head->_next != nullptr) {
            head = head->_next;
        }

        switch (optionlist) {
        case CREATE:
            cout << "Name your playlist: ";
            cin.ignore();
            getline(cin, plName);
            head->CreateNewPlaylist(plName);
            break;


            case SELECT:
                Menu::SelectPlaylist();
                Tree::PrintPlaylists(head);
                break;
            

            case PRINT:
                Tree::PrintPlaylists(head);
                break;
            

            case DELETE:
                cout << "Which playlist would you like to delete?" << endl;
                Tree::PrintPlaylists(head);
                cin.ignore();
                getline(cin, plName);
                Tree::DeletePlaylist(head, plName);
                break;


            case EXIT:
                cout << "Goodbye!" << endl;
                return;

            default:
                cout << "Please choose a valid option!" << endl;
                break;
        }
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
            cout << "Press 1 to create a playlist" << endl;
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
        menu.ProcessInput(head);

        cout << "Would you like to continue using the program? (1 for yes, 5 for no)" << endl;
        cin >> user;
        if (user == 5) {
            break;
        }
    }

    return 0;
}
