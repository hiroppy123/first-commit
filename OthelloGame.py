class OthelloGame:
    def __init__(self):
        self.board = [[' ' for _ in range(8)] for _ in range(8)]
        self.board[3][3] = 'W'
        self.board[3][4] = 'B'
        self.board[4][3] = 'B'
        self.board[4][4] = 'W'
        self.current_player = 'B'

    def print_board(self):
        print("  0 1 2 3 4 5 6 7")
        for i in range(8):
            print(i, end=" ")
            for j in range(8):
                print('|' + self.board[i][j], end="")
            print('|')

    def is_valid_move(self, row, col):
        if self.board[row][col] != ' ':
            return False
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]
        for dr, dc in directions:
            r, c = row + dr, col + dc
            while 0 <= r < 8 and 0 <= c < 8 and self.board[r][c] != ' ' and self.board[r][c] != self.current_player:
                r, c = r + dr, c + dc
                if 0 <= r < 8 and 0 <= c < 8 and self.board[r][c] == self.current_player:
                    return True
        return False

    def make_move(self, row, col):
        if not self.is_valid_move(row, col):
            return False
        self.board[row][col] = self.current_player
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]
        for dr, dc in directions:
            r, c = row + dr, col + dc
            while 0 <= r < 8 and 0 <= c < 8 and self.board[r][c] != ' ' and self.board[r][c] != self.current_player:
                r, c = r + dr, c + dc
                if 0 <= r < 8 and 0 <= c < 8 and self.board[r][c] == self.current_player:
                    r, c = row + dr, col + dc
                    while 0 <= r < 8 and 0 <= c < 8 and self.board[r][c] != ' ' and self.board[r][c] != self.current_player:
                        self.board[r][c] = self.current_player
                        r, c = r + dr, c + dc
        self.current_player = 'W' if self.current_player == 'B' else 'B'
        return True

    def play_game(self):
        while True:
            self.print_board()
            print(f"Current player: {self.current_player}")
            move = input("Enter your move (row col): ")
            try:
                row, col = map(int, move.split())
                if self.make_move(row, col):
                    if all(all(cell != ' ' for cell in row) for row in self.board):
                        self.print_board()
                        black_count = sum(row.count('B') for row in self.board)
                        white_count = sum(row.count('W') for row in self.board)
                        if black_count > white_count:
                            print("Black wins!")
                        elif white_count > black_count:
                            print("White wins!")
                        else:
                            print("It's a tie!")
                        break
                else:
                    print("Invalid move. Try again.")
            except ValueError:
                print("Invalid input. Please enter row and column as two space-separated numbers.")

othello = OthelloGame()
othello.play_game()
