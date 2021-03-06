void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete (const char board[9][9]);
bool make_move(const char position [2], const char digit, char board [9][9]);
bool is_cell_empty(const int row, const int col, const char board[9][9]);
int get_row_number(const char position[2]);
int get_col_number(const char position[2]);
bool is_position_valid(const char position[2]);
bool no_row_repeat(const int row, const char digit, const char board[9][9]);
bool no_col_repeat(const int col, const char digit, const char board[9][9]);
bool no_box_repeat(const int row, const int col, const char digit, const char board[9][9]);
bool save_board(const char *filename, const char board[9][9]);
bool solve_board(char board[9][9]);
bool make_move_quick(const int row, const int col, const char digit, char board [9][9]);
