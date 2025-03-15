extends Area2D

var screensize = Vector2.ZERO

#First, CollisionShape2D’s disabled property needs to be set to true. However, if
#you try setting it directly, Godot will complain. You’re not allowed to change
#physics properties while collisions are being processed; you have to wait until
#the end of the current frame. That’s what set_deferred() does. Next, create_tween() 
#creates a tween object, set_parallel() says that any following tweens should happen
#at the same time, instead of one after another, and set_trans() sets the transition
#function to the “quadratic” curve. After that come two lines that set up the tweening
#of the properties. tween_property() takes four parameters – the object to affect 
#(self), the property to change, the ending value, and the
#duration (in seconds).
func pickup():
	#disable the collision shape so that the coin can’t trigger further collisions
	$CollisionShape2D.set_deferred("disabled", true)
	var tw = create_tween().set_parallel().set_trans(Tween.TRANS_QUAD)
	tw.tween_property(self, "scale", scale * 3, 0.3)
	tw.tween_property(self, "modulate:a", 0.0, 0.3)
	await tw.finished
	queue_free()

func _ready() -> void:
	$Timer.start(randf_range(3, 8))
	$AnimatedSprite2d.frame = 0

func _on_timer_timeout() -> void:
	$AnimatedSprite2D.frame = 0
	$AnimatedSprite2D.play()
	
func _on_lifetime_timeout() -> void:
	queue_free()


func _on_area_entered(area: Area2D) -> void:
	if area.is_in_group("obstacles"):
		position = Vector2(randi_range(0, screensize.x), randi_range(0, screensize.y))
