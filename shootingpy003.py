import pygame
import random
import sys

# Initialize Pygame
pygame.init()

# Set screen dimensions
WIDTH, HEIGHT = 800, 600
SCREEN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Simple Shooting Game")

# Colors
WHITE = (255, 255, 255)
RED = (255, 0, 0)
BLUE = (0, 0, 255)

# Player
player_size = 50
player_pos = [WIDTH // 2 - player_size // 2, HEIGHT - 2 * player_size]
player_speed = 10

# Bullet
bullet_size = 10
bullet_speed = 10
bullets = []

# Enemy
enemy_size = 50
enemy_pos = [random.randint(0, WIDTH - enemy_size), 0]
enemy_speed = 2

# Game over flag
game_over = False

# Score
score = 0
font = pygame.font.Font(None, 36)

# Main game loop
while not game_over:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                bullet_pos = [player_pos[0] + player_size // 2 - bullet_size // 2, player_pos[1]]
                bullets.append(bullet_pos)

    # Move the player
    keys = pygame.key.get_pressed()
    if keys[pygame.K_LEFT] and player_pos[0] > 0:
        player_pos[0] -= player_speed
    if keys[pygame.K_RIGHT] and player_pos[0] < WIDTH - player_size:
        player_pos[0] += player_speed

    # Move the enemy
    enemy_pos[1] += enemy_speed

    # Check collision
    for bullet in bullets:
        if pygame.Rect(enemy_pos[0], enemy_pos[1], enemy_size, enemy_size).colliderect(pygame.Rect(bullet[0], bullet[1], bullet_size, bullet_size)):
            bullets.remove(bullet)
            score += 1
            enemy_pos = [random.randint(0, WIDTH - enemy_size), 0]
        elif bullet[1] > 0:
            bullet[1] -= bullet_speed
        else:
            bullets.remove(bullet)

    # Draw everything
    SCREEN.fill(WHITE)
    pygame.draw.rect(SCREEN, RED, (player_pos[0], player_pos[1], player_size, player_size))
    pygame.draw.rect(SCREEN, BLUE, (enemy_pos[0], enemy_pos[1], enemy_size, enemy_size))
    for bullet in bullets:
        pygame.draw.rect(SCREEN, RED, (bullet[0], bullet[1], bullet_size, bullet_size))

    # Display score
    score_text = font.render("Score: " + str(score), True, RED)
    SCREEN.blit(score_text, (10, 10))

    # Game over condition
    if pygame.Rect(player_pos[0], player_pos[1], player_size, player_size).colliderect(
            pygame.Rect(enemy_pos[0], enemy_pos[1], enemy_size, enemy_size)):
        game_over = True

    pygame.display.update()
    pygame.time.Clock().tick(30)

# Game over screen
SCREEN.fill(WHITE)
game_over_text = font.render("Game Over! Your Score: " + str(score), True, RED)
SCREEN.blit(game_over_text, (WIDTH // 2 - 200, HEIGHT // 2))
pygame.display.update()
pygame.time.delay(2000)

pygame.quit()
sys.exit()

