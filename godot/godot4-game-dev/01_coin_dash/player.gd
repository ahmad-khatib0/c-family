extends Area2D

signal pickup
signal hurt

# Using the @export annotation on the speed variable allows you to set its value in the Inspector window
@export var speed = 350
var velocity = Vector2.ZERO
var screensize = Vector2(480,720)

func _process(delta: float) -> void:
	velocity = Input.get_vector("ui_left", 'ui_right', 'ui_up', 'ui_down')
	#function to limit the player’s position to minimum and maximum values
	position += velocity * speed * delta
	position.x = clamp(position.x, 0, screensize.x)
	position.y = clamp(position.y, 0, screensize.y)
	
	if velocity.length() > 0: 
		$AnimatedSprite2D.animation = "run"
	else: 
		$AnimatedSprite2D.animation = "idle"
	
	if velocity.x != 0: 
		$AnimatedSprite2D.flip_h = velocity.x < 0
	
func start():
	set_process(true)
	position = screensize / 2
	$AnimatedSprite2D.animation = "idle"

#  called when the player hits an obstacle or runs out of time:
func die():
	$AnimatedSprite2D.animation = "hurt"
	# Using set_process(false) tells Godot to stop calling the _process() 
	# function every frame. Since the movement code is in that function,
	# you’ll no longer be able to move when the game is over.
	set_process(false)	
		
func _on_area_entered(area):
	if area.is_in_group("coins"):
		area.pickup()
		pickup.emit("coin")
	if area.is_in_group("powerups"):
		area.pickup()
		pickup.emit("powerup")
	if area.is_in_group("obstacles"):
		hurt.emit()
		die()
