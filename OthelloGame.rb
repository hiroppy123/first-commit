class OthelloGame
  def initialize
    @board = Array.new(8) { Array.new(8, ' ') }
    @board[3][3] = 'O'
    @board[3][4] = 'X'
    @board[4][3] = 'X'
    @board[4][4] = 'O'
    @current_player = 'X'
  end

  def display_board
    puts "  0 1 2 3 4 5 6 7"
    @board.each_with_index do |row, index|
      print "#{index} "
      row.each { |cell| print "#{cell} " }
      puts
    end
  end

  def valid_move?(row, col)
    return false if @board[row][col] != ' '
    # プレイヤーが石を置けるかどうかのロジックを実装
    # 省略
    true
  end

def make_move(row, col)
  directions = [[-1, 0], [1, 0], [0, -1], [0, 1], [-1, -1], [-1, 1], [1, -1], [1, 1]]
  @board[row][col] = @current_player

  directions.each do |dr, dc|
    r, c = row + dr, col + dc
    to_be_flipped = []

    while r.between?(0, 7) && c.between?(0, 7) && @board[r][c] != ' ' && @board[r][c] != @current_player
      to_be_flipped << [r, c]
      r, c = r + dr, c + dc
    end

    if r.between?(0, 7) && c.between?(0, 7) && @board[r][c] == @current_player
      to_be_flipped.each { |flip_row, flip_col| @board[flip_row][flip_col] = @current_player }
    end
  end
end

  def switch_player
    @current_player = @current_player == 'X' ? 'O' : 'X'
  end

  def play
    loop do
      display_board
      puts "Current player: #{@current_player}"
      puts "Enter row and column (e.g. 3 4):"
      input = gets.chomp
      row, col = input.split.map(&:to_i)
      if valid_move?(row, col)
        make_move(row, col)
        switch_player
      else
        puts "Invalid move! Try again."
      end
      # ゲーム終了の条件や勝利判定のロジックを実装
      # 省略
    end
  end
end

game = OthelloGame.new
game.play


