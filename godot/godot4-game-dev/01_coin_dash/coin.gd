extends Area2D

var screensize = Vector2.ZERO

func _ready():
	$Timer.start(randf_range(3, 8))
	
func pickup():
	# queue_free() is Godot’s method for removing nodes. It safely removes the
	# node from the tree and deletes it from memory, along with all its children.
	$CollisionShape2D.set_deferred("disabled", true)
	var tw = create_tween().set_parallel().set_trans(Tween.TRANS_QUAD)
	tw.tween_property(self, "scale", scale * 3, 0.3)
	tw.tween_property(self, "modulate:a", 0.0, 0.3)
	await tw.finished
	queue_free()
	
func _on_timer_timeout() -> void:
	$AnimatedSprite2D.frame = 0
	$AnimatedSprite2D.play()

# coins can spawn on top of the cactus, making them impossible to
# pick up. When the coin is placed, it needs to move if it detects
# that it’s overlapping with the obstacle.	
func _on_area_entered(area: Area2D) -> void:
	if area.is_in_group("obstacles"):
		position = Vector2(randi_range(0, screensize.x), randi_range(0, screensize.y))
