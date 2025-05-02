extends RigidBody2D

@export var engine_power = 500
@export var spin_power= 8000

var screensize = Vector2.ZERO
var thrust = Vector2.ZERO
var rotation_dir = 0


enum {INIT, ALIVE , INVULNERABLE, DEAD}

var state = INIT

func _ready() -> void:
	change_state(ALIVE)
	screensize = get_viewport().size
	
func _process(delta: float) -> void:
	get_input()
	
func get_input():
	thrust = Vector2.ZERO
	if state in [DEAD ,  INIT]:
		return
	if Input.is_action_pressed("thrust"):
		thrust = transform.x * engine_power
	rotation_dir = Input.get_axis("rotate_left", "rotate_right")

# when using physics bodies, their movement and related functions should 
# always be called in _physics_process(). Here, you can apply the forces
# set by the inputs to actually move the body.
func _physics_process(delta): 
	constant_force = thrust
	constant_torque = rotation_dir * spin_power

func _integrate_forces(physics_state: PhysicsDirectBodyState2D) -> void:
	var xform = physics_state.transform
	# The wrapf() function takes a value (the first argument) and “wraps” it 
	# between any min/max values you choose. So, if the value goes below 0, 
	# it becomes screensize.x, and vice versa.
	xform.origin.x = wrapf(xform.origin.x , 0 , screensize.x)
	xform.origin.y = wrapf(xform.origin.y , 0 , screensize.y)
	physics_state.transform = xform
	
func change_state(new_state ) :
	match new_state:
		INIT:
			$CollisionShape2D.set_deferred("disabled", true)
		ALIVE: 
			$CollisionShape2D.set_deferred("disabled", false)
		INVULNERABLE: 
			$CollisionShape2D.set_deferred("disabled", true)
		DEAD: 
			$CollisionShape2D.set_deferred("disabled", true)
	state = new_state
