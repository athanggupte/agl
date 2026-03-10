local agl = require("agl")
agl.title = "AGL LuaJIT 3D Demo"
agl.width = 1280
agl.height = 720
agl.plugins = { "fps_counter.dll", "gltf_loader.dll" }
agl.memconfig.SCRATCH_MEMORY_SIZE = 6 * 1024 * 1024 -- Increase scratch memory to 6 MiB for testing

local vec3f = agl.math.vec3f
local quatf = agl.math.quatf

local game = {}

function agl.load(ctx)
	local meshes, err
	meshes, err = ctx:loadMeshes("demon_rigged.glb")
	assert(meshes, err)
	print("Loaded "..#meshes.." mesh(es)")
	game.meshes = meshes
	ctx:getDefaultCanvas():setCameraPosition(0, 0, 5)
	ctx:getDefaultCanvas():setCameraLookAt(0, 0, 0, 0, 1, 0)
	ctx:getDefaultCanvas():setCameraPerspective(math.rad(60), 0.1, 100)
end

function agl.update(ctx, deltaTime)
	local canvas = ctx:getDefaultCanvas()
	-- angle = angle + deltaTime * math.rad(30)
	local q1 = quatf.fromAxisAngle(agl.math.vec3f.new(1, 0, 0), math.rad(90))
	local q2 = quatf.fromAxisAngle(agl.math.vec3f.new(0, 1, 0), os.clock() * math.rad(30))
	local q = quatf.mul2(q2, q1)
	canvas:drawMesh(game.meshes[1], vec3f.new(0, 0, -5), q, 4, 1, 1, 1, 1)
end

agl:run()