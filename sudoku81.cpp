#include <iostream>
#include <windows.h>

using namespace std;

int board[9][9] = {
    {0,1,0,0,5,3,7,9,8},
    {7,5,3,1,0,9,0,0,0},
    {0,2,0,4,0,7,0,0,3},
    {1,0,4,9,0,0,0,8,0},
    {0,8,0,6,0,4,0,7,0},
    {0,6,0,0,0,8,4,0,2},
    {3,0,0,8,0,5,0,6,0},
    {0,0,0,7,0,1,3,5,9},
    {5,9,1,3,4,0,0,2,0},
}; //題目 

bool editable[9][9]; //格子內是否為題目 
int cur_r = 0, cur_c = 0; //r是上下 c是左右 

int check_horizontal(int x,int y) //水平行 -1為衝突 0為未完成 1為完成
{
    /* TODO: Check if a horizontal line has conflict number, or is finished. */
    int check[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int zero=0;
	for(int i=0;i<9;i++){
		if(board[x][i]==0) {
			zero+=1;
		}
		for(int j=0;j<i;j++){
			if(board[x][i]==check[j] && board[x][i]!=0) return -1;
		}
		check[i]=board[x][i];
	}
	if(zero==0) return 1;
	else return 0;
}
int check_vertical(int x,int y) //垂直行 -1為衝突 0為未完成 1為完成 
{
    /* TODO: Check if a vertical line has conflict number, or is finished. */
    int check[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int zero=0;
	for(int i=0;i<9;i++){
		if(board[i][y]==0) {
			zero+=1;
		}
		for(int j=0;j<i;j++){
			if(board[i][y]==check[j] && board[i][y]!=0) return -1;
		}
		check[i]=board[i][y];
	}
	if(zero==0) return 1;
	else return 0;
}

int check_block(int x,int y)
{
    /* TODO: Check if a block has conflict number, or is finished. */
    
	int a=0 , b=0;
	if(x==3 || x==4 || x==5) a=3;
	if(y==3 || y==4 || y==5) b=3;
    if(x==6 || x==7 || x==8) a=6;
	if(y==6 || y==7 || y==8) b=6;
	
	int check[3][3]={{-1,-1,-1},{-1,-1,-1},{-1,-1,-1}}; 
    int zero=0;
    for(int i=0;i<3;i++){
    	for(int j=0;j<3;j++){
    		if(board[i+a][j+b]==0) zero+=1;
    		for(int m=0;m<i;m++){
    			for(int n=0;n<j;n++){
    				if(board[i+a][j+b]==check[m][n] && board[i+a][j+b]!=0) return -1;
				}
			}
			check[i+a][j+b]=board[i+a][j+b];
		}
	}
	if(zero==0) return 1;
	else return 0;
	
}

void fill_number(char c)//填入/清除數字 
{
    /* TODO: Fill a number in to the cell the cursor is now pointing to.
             After fill in the number, check the horizontal line, the
             vertical line and the block the cell is in.
     */
    board[cur_r][cur_c]=int(c-48);
}

void move_cursor(char c) //移動光標 
{
    /* TODO: Move the cursor up, down, to the left or to the right.
             Remember to check if the cursor is moving out of bound.
    */
    if(cur_r>=0 && cur_r<=8){
    	if(c=='w' || c=='W'){
			if(cur_r==0) return;
			else if(!editable[cur_r-1][cur_c]){
				int x=1;
				while(!editable[cur_r-x][cur_c]){
					x+=1;
				}
				if(cur_r-x>=0)cur_r-=x;
			}
			else cur_r-=1;
		}
		if(c=='s' || c=='S'){
			if(cur_r==8) return;
			else if(!editable[cur_r+1][cur_c]){
				int x=1;
				while(!editable[cur_r+x][cur_c]){
					x+=1;
				}
				if(cur_r+x<=8)cur_r+=x;
			}
			else cur_r+=1;
		} 
		if(c=='d' || c=='D'){
			if(cur_c==8) return;
			else if(!editable[cur_r][cur_c+1]){
				int x=1;
				while(!editable[cur_r][cur_c+x]){
					x+=1;
				}
				if(cur_c+x<=8)cur_c+=x;
			}
			else cur_c+=1;
		}
		if(c=='a' || c=='A'){
			if(cur_c==0) return;
			else if(!editable[cur_r][cur_c-1]){
				int x=1;
				while(!editable[cur_r][cur_c-x]){
					x+=1;
				}
				if(cur_c-x>=0)cur_c-=x;
			}
			else cur_c-=1;
		}
	}
}

bool is_invalid(int i, int j)
{
    /* TODO: Check if board[i][j] is in a line that has conflict numbers. */ 
    if(check_horizontal(i,j)==-1 || check_vertical(i,j)==-1 || check_block(i,j)==-1) return true;
    return false;
}

bool is_done(int i, int j)
{
    /* TODO: Check if board[i][j] is in a line that has finished. */
    if(check_horizontal(i,j)==1 || check_vertical(i,j)==1 || check_block(i,j)==1) return true;
    return false;
}

bool check_win()
{
    /* TODO: Check if the game is set. That is, every cell is finished. */
    for(int i=0;i<9;i++){
    	for(int j=0;j<9;j++){
    	if(board[i][j]==0) return 0;
		if(check_horizontal(i,j)==-1 || check_vertical(i,j)==-1 || check_block(i,j)==-1) return 0;
		} 
	}
    return 1;
}

bool is_moving_action(char c)
{
    return (c == 'W' || c == 'w' || c == 'S' || c == 's' ||
            c == 'A' || c == 'a' || c == 'D' || c == 'd');
}

bool is_filling_action(char c)
{
    return (c >= '0' && c <= '9');
}

string get_styled_text(string text, string style)
{
    string color = "", font = "";
    for (char c : style)
    {
        if (c == 'R')
            color = "31";
        if (c == 'G')
            color = "32";
        if (c == 'E')
            color = "41";
        if (c == 'C')
            color = "106";
        if (c == 'B')
            font = ";1";
    }
    return "\x1b[" + color + font + "m" + text + "\x1b[0m";
}

void print_board()
{
    // Flush the screen
    cout << "\x1b[2J\x1b[1;1H";

    // Print usage hint.
    cout << get_styled_text("W/A/S/D: ", "B") << "move cursor" << endl;
    cout << get_styled_text("    1-9: ", "B") << "fill in number" << endl;
    cout << get_styled_text("      0: ", "B") << "clear the cell" << endl;
    cout << get_styled_text("      Q: ", "B") << "quit" << endl;
    cout << endl;

    // Iterate through and print each cell.
    for (int i = 0; i < 9; ++i)
    {
        // Print horizontal divider.
        if (i && i % 9 == 0)
            cout << "---------------" << endl;

        // Print the first vertical divider in each line.
        cout << "|";
        for (int j = 0; j < 9; ++j)
        {
            // Set text style based on the state of the cell.
            string style = "";

            // Set style for the cell the cursor pointing to.
            if (cur_r == i && cur_c == j)
                style = "C";
            // Set style for the cell in an invalid line.
            if (is_invalid(i, j))
				if (cur_r == i && cur_c == j) style = "C";
				else style = "E";
            // Set style for the cell in a finished line.
            else if (is_done(i, j))
            	if (cur_r == i && cur_c == j) style = "C";
                else style = "G";

            // Set style for a the cell that is immutable.
            if (!editable[i][j])
                style += "B";

            // Print the cell out in styled text.
            // If the content is 0, print a dot, else print the number.
            if (board[i][j] == 0)
                cout << get_styled_text(" · ", style);
            else
                cout << get_styled_text(" " + to_string(board[i][j]) + " ", style);

            // Print the vertical divider for each block.
            if ((j + 1) % 3 == 0)
                cout << "|";
        }
        cout << endl;
    }
}

void initialize()
{
    // Set up styled text for Windows.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // Mark editable cells
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            editable[i][j] = !board[i][j];

    // Print the initial board out.
    print_board();
}

void sudoku81()
{
    char c;
    bool action_ok;

    initialize();
    while (cin >> c)
    {
        action_ok = false;
        if (is_moving_action(c))
        {
            action_ok = true;
            move_cursor(c);
        }

        if (is_filling_action(c))
        {
            action_ok = true;
            fill_number(c);
        }

        if (c == 'Q' || c == 'q')
            break;

        print_board();

        if (check_win())
        {
            cout << "YOU WIN!" << endl;
            break;
        }

        if (!action_ok)
            cout << get_styled_text("!!! Invalid action !!!", "R");
    }

    return;
}
int main(){
	sudoku81();
	return 0;
}
