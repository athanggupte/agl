local agl = require("agl")

agl.title = "Test App"
agl.width = 400
agl.height = 400
agl.plugins = { "fps_counter.dll" }
agl.memconfig.SCRATCH_MEMORY_SIZE = 6 * 1024 * 1024

local ground = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
}

local function groundTileAt(x, y)
	return ground[(15-y)*16 + x + 1]
end

local plyPosX, plyPosY = 7.5, 7.5
local plyVelX, plyVelY = 0, 0
local plyShouldJump = false

local function distanceToGround(x, y)
	local tileX, tileY = math.floor(x), math.floor(y)
	if tileX < 0 or tileX >= 16 or tileY < 0 or tileY >= 16 then
		return 0
	end
	if groundTileAt(tileX, tileY) == 1 then
		return 0
	else
		for checkY = tileY - 1, 0, -1 do
			if groundTileAt(tileX, checkY) == 1 then
				return y - (checkY + 1)
			end
		end
	end
	
end

local function drawTile(canvas, x, y, color)
	local ndcX, ndcY = agl.screenToNdc(x*25, (15-y)*25, 400, 400)
	local ndcW, ndcH = 25 / 400 * 2, 25 / 400 * 2
	canvas:drawScreenQuad(ndcX+ndcW/2, ndcY-ndcH/2, ndcW, ndcH, 0, color, nil)
end

agl.update = function(context, deltaTime)
 	local canvas = context:getDefaultCanvas()
	-- Update
	local plyAccY = 0
	if distanceToGround(plyPosX, plyPosY) > 0 then
		plyAccY = -50
	else
		plyPosY = math.floor(plyPosY + 0.5)
		plyVelY = 0
		if plyShouldJump then
			plyVelY = 15
			plyShouldJump = false
		end
	end
	
	plyVelX = 0
	if context.isKeyDown(context, agl.KEY_LEFT) then
		plyVelX = -5
	end
	if context.isKeyDown(context, agl.KEY_RIGHT) then
		plyVelX = 5
	end
	plyVelY = plyVelY + plyAccY * deltaTime
	plyPosX = plyPosX + plyVelX * deltaTime
	plyPosY = plyPosY + plyVelY * deltaTime

	-- Draw
	for y=0,15 do
		for x=0,15 do
			if groundTileAt(x, y) == 1 then
				drawTile(canvas, x, y, 0xFF00FF00)
			end
		end
	end
	do
		drawTile(canvas, plyPosX, plyPosY, 0xFF0000FF)
	end
end

agl.onkey = function(context, key, action, repeat_)
	if key == agl.KEY_SPACE then
		if action == 1 and repeat_ ~= 1 then -- press
			if distanceToGround(plyPosX, plyPosY) == 0 then
				plyShouldJump = true
			end
		end
	end
end

agl:run()