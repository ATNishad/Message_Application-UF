#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

struct message_structure {
  string content;
  string timestamp;
  message_structure(string A, string B) : content(A), timestamp(B) {}
};
struct sender_structure {
  string username;
  vector<message_structure> message;

  void set_sender(string name) { this->username = name; }
  void set_message(string content, string timestamp) {
    message.push_back((message_structure(content, timestamp)));
  }
};

const string timer() {
  const auto now = chrono::system_clock::now();
  time_t t = chrono::system_clock::to_time_t(now);
  string timestamp = std::ctime(&t);
  timestamp.pop_back();
  return timestamp;
}

void user_menu() {
  cout << "\n";
  cout << "-----MENU-----\n";
  cout << "1.REGISTER-new user.\n";
  cout << "2.LOGIN-existing user.\n";
  cout << "3.Display users.\n";
  cout << "4.EXIT.\n";
  cout << "Enter your choice:";
}
void msg_menu() {
  cout << "\n-----MENU-----\n";
  cout << "1. Send Messages.\n";
  cout << "2. View Messages.\n";
  cout << "3. Edit Message.\n";
  cout << "4. Delete Message.\n";
  cout << "5. Save & Exit.\n";
  cout << "Enter your choice: ";
}

void user_register(vector<sender_structure> &sender_vector) {
  string name;
  cout << "Enter name to register:";
  getline(cin, name);
  sender_structure sender_object;
  sender_object.set_sender(name);
  sender_vector.push_back(sender_object);
}

void user_login(vector<sender_structure> &sender_vector,bool &global_user_logged,sender_structure *&current_user_pointer) {
  string username;
  cout << "Enter your username:";
  getline(cin, username);
  for (auto &sender : sender_vector) {
    if (sender.username == username) {
      current_user_pointer = &sender;
      global_user_logged = true;
      return;
    }
  }
  global_user_logged = false;
}

const void user_display(const vector<sender_structure> &sender_vector){
for(const auto itr : sender_vector){
  cout<<itr.username;
  cout<<",";
}
  cout<<"\n";
}

void send_message(vector<sender_structure> &sender_vector,sender_structure* &current_user_pointer){
  string content;
  cout<<"Enter message:";
  getline(cin,content);
  current_user_pointer->set_message(content,timer());
  cout<<"Message sent successfully!\n";
}

const void view_message(vector<sender_structure> &sender_vector,sender_structure* &current_user_pointer){
  for(const auto itr : sender_vector){
    if(itr.username == current_user_pointer->username){
      for(const auto itr : current_user_pointer->message )
      cout<<itr.content<<" "<<"["<<itr.timestamp<<"]"<<"\n";
    }
  }
}

void edit_message(vector<sender_structure> &sender_vector,sender_structure* &current_user_pointer){
  int display_index = 0;
  int edit_index;
  string content;

  for(auto itr = current_user_pointer->message.begin();itr != current_user_pointer->message.end();++itr , display_index++){
    cout<<"["<<display_index<<"]"<<itr->content;
    cout<<"\n";
  }

  cout<<"Enter message index to edit:";
  cin>>edit_index;
  cin.ignore();
  cout<<"Enter new message:";
  getline(cin,content);
  int index = 0;
  for(auto &itr : current_user_pointer->message){
    if(index == edit_index){
      itr.content = content;
      cout<<"Message edited successfully!\n";
    }index++;
  }
}

int main() {
  int user_choice;
  int msg_choice;
  bool global_user_logged = false;
  vector<sender_structure> sender_vector;
  sender_structure *current_user_pointer = nullptr;

  // user_menu_do
  do {
    user_menu();
    cin >> user_choice;
    cin.ignore();
    switch (user_choice) {
    case 1:
      user_register(sender_vector);
      break;

    case 2:
      user_login(sender_vector, global_user_logged, current_user_pointer);
      if(global_user_logged){
      cout<<"LOGIN SUCCESSFULL!";
      }
      else{
        cout<<"LOGIN FAILED!";
      }
      break;

    case 3:
      user_display(sender_vector);
      break;
    case 4:
      cout << "Exited program.";
      return 0;
    }
  } while (!global_user_logged);

//msg menu do
  do {
    msg_menu();
    cin >> msg_choice;
    cin.ignore();
    switch (msg_choice) {
      case 1:
      send_message(sender_vector,current_user_pointer);
      break;

      case 2:
      view_message(sender_vector,current_user_pointer);
      break;
      
      case 3:
      edit_message(sender_vector,current_user_pointer);
      break;
      
      case 4:
      break;
    
      case 5:
      break;
    }
  } while (msg_choice != 5);
}
