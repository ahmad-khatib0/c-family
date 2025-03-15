extends Node

# Drag coin.tscn from the FileSystem panel and drop it into the Coin Scene property.
@export var coin_scene : PackedScene
@export var powerup_scene : PackedScene
@export var playtime = 30

var level
var score
var time_left
var screensize
var playing = false

#Godot automatically calls _ready() on every node when it’s added. This is a good place to put code
#that you want to happen at the beginning of a node’s lifetime.
func _ready() -> void:
	randomize()
	screensize = get_viewport().get_visible_rect().size
	$Player.screensize = screensize
	$Player.hide() # hide player on starting game
	
# The new_game() function will initialize everything for a new game:
func new_game():
	playing = true 
	level = 1
	score = 0
	time_left = playtime
	$Player.start()
	$Player.show()
	$GameTimer.start()
	spawn_coins()
	$HUD.update_score(score)
	$HUD.update_timer(time_left)
	spawn_coins()
	
func spawn_coins():
	$LevelSound.play()
	for i in level + 4:
		# dynamically create new objects in code using instantiate().
		var c = coin_scene.instantiate()
		add_child(c)
		c.screensize = screensize
		c.position = Vector2(randi_range(0, screensize.x), randi_range(0, screensize.y))

func _process(delta: float) -> void:
	#If no more coins remain, then the player advances to the next level.
	if playing and get_tree().get_nodes_in_group("coins").size() == 0:
		level += 1
		time_left += 5
		spawn_coins()
		$PowerupTimer.wait_time = randf_range(5, 10)
		$PowerupTimer.start()
		
func game_over():
	$EndSound.play()
	playing = false
	$GameTimer.stop()
	#remove all remaining coins by calling queue_free() on each of them.
	get_tree().call_group("coins", "queue_free")
	$HUD.show_game_over()
	$Player.die()

func _on_player_hurt() -> void:
	game_over()

func _on_game_timer_timeout() -> void:
	time_left -= 1
	$HUD.update_timer(time_left)
	if time_left <= 0:
		game_over()

func _on_player_pickup(type):
	match type:
		"coin":
			$CoinSound.play()
			score += 1
			$HUD.update_score(score)
		"powerup":
			$PowerupSound.play()
			time_left += 5
			$HUD.update_timer(time_left)

func _on_hud_start_game() -> void:
	new_game()

func _on_powerup_timer_timeout() -> void:
	var p = powerup_scene.instantiate()
	add_child(p)
	p.screensize = screensize
	p.position = Vector2(randi_range(0, screensize.x), randi_range(0, screensize.y))
