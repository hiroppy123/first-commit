import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.Random;

public class SimpleShootingGame003 extends JFrame implements KeyListener {
    private final int WIDTH = 800;
    private final int HEIGHT = 600;
    private final int PLAYER_SIZE = 50;
    private final int ENEMY_SIZE = 50;
    private final int BULLET_SIZE = 10;
    private final int PLAYER_SPEED = 10;
    private final int BULLET_SPEED = 10;
    private final int ENEMY_SPEED = 2;

    private int playerX = WIDTH / 2 - PLAYER_SIZE / 2;
    private int playerY = HEIGHT - 2 * PLAYER_SIZE;
    private boolean leftKeyPressed, rightKeyPressed, spaceKeyPressed;

    private ArrayList<int[]> bullets = new ArrayList<>();
    private int enemyX = new Random().nextInt(WIDTH - ENEMY_SIZE);
    private int enemyY = 0;
    private int score = 0;
    private boolean gameover = false;

    public SimpleShootingGame003() {
        setTitle("Simple Shooting Game");
        setSize(WIDTH, HEIGHT);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setResizable(false);
        addKeyListener(this);
        setVisible(true);

        Timer timer = new Timer(30, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (!gameover) {
                    movePlayer();
                    moveEnemy();
                    moveBullets();
                    checkCollision();
                    repaint();
                }
            }
        });
        timer.start();
    }

    public void paint(Graphics g) {
        super.paint(g);
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, WIDTH, HEIGHT);

        g.setColor(Color.RED);
        g.fillRect(playerX, playerY, PLAYER_SIZE, PLAYER_SIZE);

        g.setColor(Color.BLUE);
        g.fillRect(enemyX, enemyY, ENEMY_SIZE, ENEMY_SIZE);

        g.setColor(Color.RED);
        for (int[] bullet : bullets) {
            g.fillRect(bullet[0], bullet[1], BULLET_SIZE, BULLET_SIZE);
        }

        g.setColor(Color.RED);
        g.setFont(new Font("Arial", Font.BOLD, 20));
        g.drawString("Score: " + score, 10, 30);

        if (gameover) {
            g.setColor(Color.RED);
            g.setFont(new Font("Arial", Font.BOLD, 36));
            g.drawString("Game Over! Your Score: " + score, WIDTH / 2 - 200, HEIGHT / 2);
        }
    }

    private void movePlayer() {
        if (leftKeyPressed && playerX > 0) {
            playerX -= PLAYER_SPEED;
        }
        if (rightKeyPressed && playerX < WIDTH - PLAYER_SIZE) {
            playerX += PLAYER_SPEED;
        }
    }

    private void moveEnemy() {
        enemyY += ENEMY_SPEED;
        if (enemyY >= HEIGHT) {
            enemyX = new Random().nextInt(WIDTH - ENEMY_SIZE);
            enemyY = 0;
        }
    }

    private void moveBullets() {
        for (int i = 0; i < bullets.size(); i++) {
            int[] bullet = bullets.get(i);
            bullet[1] -= BULLET_SPEED;
            if (bullet[1] <= 0) {
                bullets.remove(i);
                i--;
            }
        }
    }

    private void checkCollision() {
        for (int[] bullet : bullets) {
            if (enemyX < bullet[0] && bullet[0] < enemyX + ENEMY_SIZE &&
                    enemyY < bullet[1] && bullet[1] < enemyY + ENEMY_SIZE) {
                score++;
                enemyX = new Random().nextInt(WIDTH - ENEMY_SIZE);
                enemyY = 0;
                bullets.remove(bullet);
                break;
            }
        }
        if (playerX < enemyX + ENEMY_SIZE && enemyX < playerX + PLAYER_SIZE &&
                playerY < enemyY + ENEMY_SIZE && enemyY < playerY + PLAYER_SIZE) {
            gameover = true;
        }
    }

    @Override
    public void keyTyped(KeyEvent e) {}

    @Override
    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT) {
            leftKeyPressed = true;
        }
        if (key == KeyEvent.VK_RIGHT) {
            rightKeyPressed = true;
        }
        if (key == KeyEvent.VK_SPACE) {
            bullets.add(new int[]{playerX + PLAYER_SIZE / 2 - BULLET_SIZE / 2, playerY});
        }
    }

    @Override
    public void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();
        if (key == KeyEvent.VK_LEFT) {
            leftKeyPressed = false;
        }
        if (key == KeyEvent.VK_RIGHT) {
            rightKeyPressed = false;
        }
    }

    public static void main(String[] args) {
        new SimpleShootingGame003();
    }
}

