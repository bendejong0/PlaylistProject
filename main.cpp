#include <iostream>
#include <string>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
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
            cout << "Song title: " << current -> _title << ", Artist name: " <<  current -> _artist << ", Song ID: " << _songId << endl;
            current = current -> _next;
        }
        cout << "Song title: " << current -> _title << ", Artist name: " <<  current -> _artist << ", Song ID: " << _songId << endl;
    }

    void DeleteSong(Node* current, string songTitle = "", string artistName = "", long songID = 0){
        Node* previous = current;
        while( ( current -> _title != songTitle && current  -> _artist != artistName ) ||  current  -> _songId != songID){
            previous = current;
            current = current -> _next;
        }
        if ((current -> _title == songTitle && current -> _artist == artistName) ||  current -> _songId == songID){
            Node* deleteThisNode = current;
            current = current -> _next;
            delete deleteThisNode;
            previous -> _next = current;
        }
    }
    void DeleteAllSongs(Node* head){
        Node* prev = head;
        while(head!=nullptr){
            head = head -> _next;
            delete prev;
            prev = head;
        }
        delete head;
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

    void PrintPlaylists(Tree* head){
        Tree* temp = head -> _next;
        // this should never come up, but incase it does, we skip it.
        if(temp -> _playlistName == "HEAD92903449"){
            temp = temp -> _next;
        }
        while(temp -> _next != nullptr){
            cout << temp -> _playlistName << endl;
            temp = temp -> _next;
        }
        cout << temp -> _playlistName << endl;
    }

    void CreateNewPlaylist(Tree* head, string newPlaylistName) {
        transform(newPlaylistName.begin(), newPlaylistName.end(), newPlaylistName.begin(), ::toupper);
        Tree* current = head -> _next;
        while (current->_next != nullptr) {
            current = current->_next;
        }
        Tree* newPlaylist = new Tree(newPlaylistName);
        current->_next = newPlaylist;
    }

    void DeletePlaylist(Tree* head, string playlistName){
        Tree* current = head;
        Tree* previous = current;
        Node node; // making a node object so we can access the functions in the Node class.

        transform(playlistName.begin(), playlistName.end(), playlistName.begin(), ::toupper);

        while(current -> _playlistName != playlistName){
            previous = current;
            current = current -> _next;
        }
        if(current -> _playlistName == playlistName){
            if(current->_next == nullptr){
                previous -> _next = nullptr;
                node.DeleteAllSongs(current -> _firstSongAddress);
                delete current;
                return;
            }
            else{
                node.DeleteAllSongs(current -> _firstSongAddress);
                Tree* deleteThisNode = current;
                current = current -> _next;
                delete deleteThisNode;
                previous -> _next = current;
            }
        }
        else{
            cout << "Playlist not found!" << endl;
            return;
        }
        // end of function
    }
    // end of the tree class.
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
    void SelectPlaylist(Tree* head){
        Tree* current = head -> _next;
        
        // a variable to count how many playlists we have.
        Tree* firstIteration = current;
        int playlistCounter=1;
        while(firstIteration -> _next != nullptr){
            playlistCounter++;
            firstIteration = firstIteration -> _next;
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
        cin.ignore();
        playlistMap.find(user);
        cout << endl << "Opening..."  << endl << endl;
        
        
        enum songOptions{
            ADD = 1,
            DELETE = 2,
            PRINT = 3,
            EXIT = 4
        };
        
        songOptions songOption;
        //this is used to select what the user wants to do to the songs in their playlist.
        int songSelectUser;
        
        
        string songTitle;
        string artistName;
        long songID;

        if(current-> _firstSongAddress == nullptr){
            int addOrGoBack;
            cout << "This playlist is empty!" << endl;
            cout << " 1) Add a song\n 2) Go back" << endl;
            cout << "Input your option's corresponding number: ";
            cin >> addOrGoBack;
            cin.ignore();


            if(addOrGoBack == 1){
                long songID;
                cout << "Enter the song's title: ";
                getline(cin, songTitle);
                cin.ignore();
                cout << "Enter the artist's name: ";
                getline(cin, artistName);
                cin.ignore();
                cout << "Enter the song's ID: ";
                cin >> songID;
                cin.ignore();
                transform(songTitle.begin(), songTitle.end(), songTitle.begin(), ::toupper);
                transform(artistName.begin(), artistName.end(), artistName.begin(), ::toupper);
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
        
        else if(current -> _firstSongAddress != nullptr){
            Node* firstSong = current -> _firstSongAddress;

            cout << "What would you like to do?\n 1) Add a song\n 2) Delete a song\n 3) Show songs\n 4) Go back" << endl;
            cin >> songSelectUser;
            cin.ignore();
            songOption = static_cast<songOptions>(songSelectUser);

            // we will need this data for cases ADD and DELETE.
            string songTitle;
            string artistName;
            long songID;

            // we need this node so we can access the addsong and deletesong functions.
            Node node;

            switch(songOption){
                case ADD:
                    cout << "Enter the song's title: ";
                    getline(cin, songTitle);
                    cin.ignore();
                    cout << "Enter the artist's name: ";
                    getline(cin, artistName);
                    cin.ignore();
                    cout << "Enter the song's ID: ";
                    cin >> songID;
                    node.AddSong(firstSong, songTitle, artistName, songID);

                    break;

                case DELETE:
                    
                    cout << "We need some info! Please tell us what you rememeber.\nEnter 0 if you don't remember the Song's ID number" << endl;
                    cout << "Enter the song's title: ";
                    getline(cin, songTitle);
                    cin.ignore();
                    cout << "Enter the artist's name: ";
                    getline(cin, artistName);
                    cin.ignore();
                    cout << "Enter the song's ID: ";
                    cin >> songID;
                    cin.ignore();

                    // convert everything to uppercase.
                    transform(songTitle.begin(), songTitle.end(), songTitle.begin(), ::toupper);
                    transform(artistName.begin(), artistName.end(), artistName.begin(), ::toupper);
                    if(songID == 0){
                        node.DeleteSong(firstSong, songTitle, artistName);
                    }
                    else{
                        node.DeleteSong(firstSong, songTitle, artistName, songID);
                    }
                    break;

                case PRINT:
                    node.PrintSong(firstSong);
                    break;
            }

        }
    }

    // function that processes user input
    int ProcessInput(Tree* head) {
        Tree* current = head -> _next;
        string plName;
        int user;
        cin >> user;
        cin.ignore();
        options optionlist = static_cast<options>(user);
        Tree tree;

        //a big important switch that processes user inputs
        switch (optionlist) {

            case CREATE:
                cout << "Name your playlist: ";
                getline(cin, plName);
                cin.ignore();
                // clear the buffer.
                current->Tree::CreateNewPlaylist(head, plName);
                return 0;


            case SELECT:
                cout << endl;
                Menu::SelectPlaylist(head);
                cout << endl << endl;
                return 0;
            

            case PRINT:
                cout << "All playlists: " << endl << endl;
                if(current -> _playlistName == ""){
                    cout << "You have no playlists!" << endl;
                    return 0;
                }
                Tree::PrintPlaylists(head);
                cout << endl;
                return 0;
            
            // if the user wants to delete a playlist,
            case DELETE:
                cout << "Which playlist would you like to delete?" << endl;
                Tree::PrintPlaylists(head);
                getline(cin, plName); // we get the playlist name,
                cin.ignore();
                transform(plName.begin(), plName.end(), plName.begin(), ::toupper);
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
    cin.ignore();

    Tree* head = new Tree(); // the head node, an undeletable node that points to the first playlist.
                // this should solve the issue of the user deleting the first playlist, which makes the program crash.

    head -> _playlistName = "HEAD92903449"; // just a super large prime number. If the playlist name is this, we know it's the head node.
                                            // meaning that we can not print it's data, since the user did not make it.

    Tree* firstPlaylist = new Tree();     // the first playlist. The user can do whatever they want to it, but it doesnt matter because the head node will always exist.
                             // this keeps our data structure safe.
        
    if (user == 1) {
        cout << "Name your playlist: ";
        getline(cin, plName);
        transform(plName.begin(), plName.end(), plName.begin(), ::toupper);
        firstPlaylist -> _playlistName = plName;
        head -> _next = firstPlaylist;
    }
    else {
       while (true) {
            cout << "Please choose a valid option!" << endl;
            cout << "Press 1 to create your first playlist" << endl;
            cin >> user;
            cin.ignore();
            if (user == 1) {
                cout << "Name your playlist: ";
                getline(cin, plName);
                transform(plName.begin(), plName.end(), plName.begin(), ::toupper);
                firstPlaylist -> _playlistName = plName;
                head -> _next = firstPlaylist;
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
