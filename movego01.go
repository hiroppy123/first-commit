package main

import "fmt"

func main() {
var x, y, n int
fmt.Scan(&x, &y, &n)
dir := 0 // 初期方向: 北 (0)、東 (1)、南 (2)、西 (3)
// すべての動きを繰り返す
for i := 0; i < n; i++ {
    var move string
    fmt.Scan(&move) // 各移動の方向を読み取る
    if move == "L" {
        dir = (dir + 3) % 4 // 初期方向: 北 (0)、東 (1)、南 (2)、西 (3)
    } else {
        dir = (dir + 1) % 4 // 方向を右に変更
    }
    // 現在の方向に基づいて x 座標と y 座標の変化を計算します
    dx, dy := 0, 0
    if dir == 0 {
        dy = 1 // 北
    } else if dir == 1 {
        dx = 1 // 東
    } else if dir == 2 {
        dy = -1 // 南
    } else if dir == 3 {
        dx = -1 // 西
    }
    x += dx // x 座標を更新します
    y += dy // y 座標を更新しますe
    fmt.Println(x, y) // 現在の座標を出力
}
}
