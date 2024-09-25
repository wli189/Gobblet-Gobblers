/*
    Author: Weitao Li
    Last date modified: April 15, 2024
    Description: It is a Gobblet Gobblers game, which is a variation of tic-tac-toe.
    The game is played on a 3x3 board.
    Each player has six pieces. Three sizes: small, medium, and large, with two pieces per size.
    The players take turns placing their pieces on the board, with the goal of getting three pieces of the same color in a row, column, or diagonal.
*/
#include <iostream>

using namespace std;

class Board {
public:
    string board[9];
    int piecesRemaining[3][3]; // 0: total piece, 1: yellow; 2: red; 0: small; 1: medium; 2: large

    Board() {
        for(int i = 0; i < 9; i++) {
            board[i] = " "; // Represent no piece.
        }

        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                piecesRemaining[i][j] = 2; // Each player starts with 2 pieces of each size.
            }
        }

        piecesRemaining[0][0] = 12; // Number of total piece
    }

    string getColor(string piece) {
        if(piece == "y" || piece == "Y" || piece == "YY") {
            return "Y"; // Yellow
        }
        else if(piece == "r" || piece == "R" || piece == "RR") {
            return "R"; // Red
        }
        else {
            return " "; // No piece
        }    
    }

    string getSize(string piece) {
        if(piece == "y" || piece == "r") {
            return "S"; // Small
        }
        else if(piece == "Y" || piece == "R") {
            return "M"; // Medium
        }
        else if(piece == "YY" || piece == "RR") {
            return "L"; // Large
        }
        else {
            return " "; // No piece
        }
    }
    
    void displayBoard() const;
    void displayPieceRemaining(string currentPlayer) const;
};


class BoardNode
{
private:
    Board data;
    BoardNode *link;
    string currentPlayer;
public:
    BoardNode();
    BoardNode(Board theData, BoardNode *theLink=nullptr, string player="yellow"); 
    BoardNode* getLink() const;
    Board getData() const;
    void setData(Board theData);
    void setLink(BoardNode* theLink);
    string getCurrentPlayer() const;
    void setCurrentPlayer(string player);
};


class BoardList {
private:
    BoardNode* head;
    int count; // Counting how many moves
public:
    BoardList();
    Board removeFromEnd(string& player);
    void addToBeginning(Board board, string player);
	void addToEnd(Board board, string player);
    int getCount() const;
};


BoardNode::BoardNode() {
    this->link = nullptr;
}

BoardNode::BoardNode(Board theData, BoardNode *theLink, string player) {
    this->data = theData;
    this->link = theLink;
    this->currentPlayer = player;
}

BoardNode* BoardNode::getLink() const {
    return link;
}

Board BoardNode::getData() const {
    return data;
}

void BoardNode::setData(Board theData) {
    this->data = theData;
}
void BoardNode::setLink(BoardNode* theLink) {
    this->link = theLink;
}

BoardList::BoardList() {
    head = nullptr;
    count = 0;
}

string BoardNode::getCurrentPlayer() const {
    return currentPlayer;
}

void BoardNode::setCurrentPlayer(string player) {
    this->currentPlayer = player;
}

// Add a board to the beginning of the list
void BoardList::addToBeginning(Board board, string player) {
	BoardNode* newNode = new BoardNode(board, nullptr, player);
	newNode->setLink(head);
	head = newNode;
    count++;
}

// Add a board to the end of the list
void BoardList::addToEnd(Board board, string player) {
	// If there is no element in the list, add the board to the beginning
    if (head == nullptr) {
		addToBeginning(board, player);
		return;
	}

	BoardNode* current = head;
	while (current->getLink() != nullptr) {
		current = current->getLink();
	}

	BoardNode* newNode = new BoardNode(board, nullptr, player);
	current->setLink(newNode);

    count++;
}

// Remove a board from the end of the list and return it
Board BoardList::removeFromEnd(string &player) {
	BoardNode* current = head;
	BoardNode* prev = nullptr;
    Board lastMove;

	while (current->getLink() != nullptr) {
		prev = current;
		current = current->getLink();
	}

    // Get the data from prev and remove current from the list
    lastMove = prev->getData();
    player = prev->getCurrentPlayer(); // Get the player of the last move
	prev->setLink(nullptr);
	delete current;

    count--;
    return lastMove;
}


// Get the count of nodes in the list
int BoardList::getCount() const {
    return count;
}


// Display the game board.
void Board::displayBoard() const {
    for(int i = 0; i < 9; i++) {
        if(i % 3 == 0 && i != 0) {
            cout << endl << "--------" << endl;
        }
        if(board[i] == "RR" || board[i] == "YY") {
            cout << board[i];
            if(!(i == 2 || i == 5 || i == 8)) {
                cout << "|";
            }
        }
        else {
            cout << board[i] << i + 1;
            if(!(i == 2 || i == 5 || i == 8)) {
                cout << "|";
            }
        }
    }
    cout << endl << endl;
}

// Display the number of piece remaining.
void Board::displayPieceRemaining(string currentPlayer) const {
    if(currentPlayer == "yellow"){
        cout << "a. YY  " << piecesRemaining[1][2] << " remain." << endl;
        cout << "b. Y   " << piecesRemaining[1][1] << " remain." << endl;
        cout << "c. y   " << piecesRemaining[1][0] << " remain." << endl;
        cout << "q to exit." << endl;
        cout << endl;
    }
    if(currentPlayer == "red") {
        cout << "a. RR  " << piecesRemaining[2][2] << " remain." << endl;
        cout << "b. R   " << piecesRemaining[2][1] << " remain." << endl;
        cout << "c. r   " << piecesRemaining[2][0] << " remain." << endl;
        cout << "q to exit." << endl;
        cout << endl;
    }    
}

// This function checks whether there is a winner. A player wins if they have three pieces of the same color in a row, column, or diagonal.
bool checkForWin(Board& Board) {
    // Check rows.
    if(Board.getColor(Board.board[0]) != " " && Board.getColor(Board.board[0]) == Board.getColor(Board.board[1]) && Board.getColor(Board.board[1]) == Board.getColor(Board.board[2])) {
        return true;
    }
    if(Board.getColor(Board.board[3]) != " " && Board.getColor(Board.board[3]) == Board.getColor(Board.board[4]) && Board.getColor(Board.board[4]) == Board.getColor(Board.board[5])) {
        return true;
    }
    if(Board.getColor(Board.board[6]) != " " && Board.getColor(Board.board[6]) == Board.getColor(Board.board[7]) && Board.getColor(Board.board[7]) == Board.getColor(Board.board[8])) {
        return true;
    }

    // Check columns.
    if(Board.getColor(Board.board[0]) != " " && Board.getColor(Board.board[0]) == Board.getColor(Board.board[3]) && Board.getColor(Board.board[3]) == Board.getColor(Board.board[6])) {
        return true;
    }
    if(Board.getColor(Board.board[1]) != " " && Board.getColor(Board.board[1]) == Board.getColor(Board.board[4]) && Board.getColor(Board.board[4]) == Board.getColor(Board.board[7])) {
        return true;
    }
    if(Board.getColor(Board.board[2]) != " " && Board.getColor(Board.board[2]) == Board.getColor(Board.board[5]) && Board.getColor(Board.board[5]) == Board.getColor(Board.board[8])) {
        return true;
    }

    // Check diagonals.
    if(Board.getColor(Board.board[0]) != " " && Board.getColor(Board.board[0]) == Board.getColor(Board.board[4]) && Board.getColor(Board.board[4]) == Board.getColor(Board.board[8])) {
        return true;
    }
    if(Board.getColor(Board.board[2]) != " " && Board.getColor(Board.board[2]) == Board.getColor(Board.board[4]) && Board.getColor(Board.board[4]) == Board.getColor(Board.board[6])) {
        return true;
    }
    return false;
}

// This function checks if the game has ended in a tie.
bool checkForTieGame(Board& Board) {
    bool isTieGame = false;
    if(Board.piecesRemaining[0][0] == 0) {
        isTieGame = true;
    }    
    return isTieGame;
}

// This function controls the player moves.
void moveOnBoard(Board& Board, string currentPlayer, string move, BoardList moveTracking){
    do{
        Board.displayBoard();
        Board.displayPieceRemaining(currentPlayer);
    
        do {
            cout << "It is " << currentPlayer << "'s turn.";
            cout << "Choose action and location, for example a2: ";
            cin >> move;

            // Input of u should undo the last step
            if (move == "u" || move == "U") {
                if (moveTracking.getCount() > 1) { // Ensure there is a move to undo
                    Board = moveTracking.removeFromEnd(currentPlayer); // Remove the last element from the BoardList
                    Board.displayBoard(); // Display the updated board
                    if (!checkForWin(Board)) {
                        Board.displayPieceRemaining(currentPlayer);
                    }
                } else {
                    cout << "Cannot undo." << endl;
                }
                continue;
            }

            char size = move[0];
            int position = move[1] - '0';
            
            // Check if the move is valid. The position should be between 1 and 9, the size should be chosen from 'a', 'b', or 'c'.
            if((position >= 1 && position <= 9) && (size == 'a' || size == 'b' || size == 'c') && (move.size() == 2)) {
                // If the current player is "yellow".
                if(currentPlayer == "yellow") {
                    if(size == 'a') {
                        // If the size of the piece at the position is large or there are no large pieces remaining for the player, it's an invalid move. If the move is not valid, ask the player to try again.
                        if(Board.getSize(Board.board[position-1]) == "L" || Board.piecesRemaining[1][2] == 0) {
                            cout << "Invalid move. Try again." << endl << endl;
                            continue;
                        }
                        Board.board[position-1] = "YY";
                        Board.piecesRemaining[1][2]--;
                        Board.piecesRemaining[0][0]--;
                    }
                    else if(size == 'b') {
                        // If the size of the piece at the position is large or medium or there are no large pieces remaining for the player, it's an invalid move. If the move is not valid, ask the player to try again.
                        if(Board.getSize(Board.board[position-1]) == "L" || Board.getSize(Board.board[position-1]) == "M" || Board.piecesRemaining[1][1] == 0) {
                            cout << "Invalid move. Try again." << endl << endl;
                            continue;
                        }
                        Board.board[position-1] = "Y";
                        Board.piecesRemaining[1][1]--;
                        Board.piecesRemaining[0][0]--;
                    }
                    else if(size == 'c') {
                        // If the size of the piece at the position is large, medium or small or there are no large pieces remaining for the player, it's an invalid move. If the move is not valid, ask the player to try again.
                        if(Board.getSize(Board.board[position-1]) == "L" || Board.getSize(Board.board[position-1]) == "M" || Board.getSize(Board.board[position-1]) == "S" || Board.piecesRemaining[1][0] == 0) {
                            cout << "Invalid move. Try again." << endl << endl;
                            continue;
                        }
                        Board.board[position-1] = "y";
                        Board.piecesRemaining[1][0]--;
                        Board.piecesRemaining[0][0]--;
                    }
                    currentPlayer = "red"; // Switch the current player.
                }
                // If the current player is "red".
                else if(currentPlayer == "red") {
                    if(size == 'a') {
                        // If the size of the piece at the position is large or there are no large pieces remaining for the player, it's an invalid move. If the move is not valid, ask the player to try again.
                        if(Board.getSize(Board.board[position-1]) == "L" || Board.piecesRemaining[2][2] == 0) {
                            cout << "Invalid move. Try again." << endl << endl;
                            continue;
                        }
                        Board.board[position-1] = "RR";
                        Board.piecesRemaining[2][2]--;
                        Board.piecesRemaining[0][0]--;
                    }
                    else if(size == 'b') {
                        // If the size of the piece at the position is large or medium or there are no large pieces remaining for the player, it's an invalid move. If the move is not valid, ask the player to try again.
                        if(Board.getSize(Board.board[position-1]) == "L" || Board.getSize(Board.board[position-1]) == "M" || Board.piecesRemaining[2][1] == 0) {
                            cout << "Invalid move. Try again." << endl << endl;
                            continue;
                        }
                        Board.board[position-1] = "R";
                        Board.piecesRemaining[2][1]--;
                        Board.piecesRemaining[0][0]--;

                    }
                    else if(size == 'c') {
                        // If the size of the piece at the position is large, medium or small or there are no large pieces remaining for the player, it's an invalid move. If the move is not valid, ask the player to try again.
                        if(Board.getSize(Board.board[position-1]) == "L" || Board.getSize(Board.board[position-1]) == "M" || Board.getSize(Board.board[position-1]) == "S" || Board.piecesRemaining[2][0] == 0) {
                            cout << "Invalid move. Try again." << endl << endl;
                            continue;
                        }
                        Board.board[position-1] = "r";
                        Board.piecesRemaining[2][0]--;
                        Board.piecesRemaining[0][0]--;
                    }
                    currentPlayer = "yellow"; // Switch the current player.
                }
                moveTracking.addToEnd(Board, currentPlayer);
                break;
            }
            // If the move is "q", exit the program.
            else if(move == "q") {
                return;
            }
            // If the move is not valid, ask the player to try again.
            else {
                cout << "Invalid move. Try again." << endl << endl;
                continue;
            }
        } while(true);

        // Display winner information.
        if(checkForWin(Board)) {
            if(currentPlayer == "yellow") {
                Board.displayBoard();
                cout << "Red wins!" << endl;
            }
            if(currentPlayer == "red") {
                Board.displayBoard();
                cout << "Yellow wins!" << endl;
            }
            
            return;  // End the program if there's a winner.
        }

        // Check if the game has ended in a tie.
        if(checkForTieGame(Board) == true) {
            Board.displayBoard();
            cout << "Tie game." << endl;

            return;  // End the program if there's a tie game.
        }
    } while(true);
}

int main() {
    Board Board;
    string currentPlayer = "yellow";
    string move;
    BoardList moveTracking; // This should be declared globally or as a member of a higher-level class


    moveTracking.addToEnd(Board, currentPlayer);
    moveOnBoard(Board, currentPlayer, move, moveTracking);
    
    return 0;
}