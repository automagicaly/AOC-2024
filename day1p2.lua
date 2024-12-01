print("AOC 2024 - day 1 - part 2")
local la = {}
local lb = {}
local lb_ = {}
local mt = {
    __index = function(_, k)
        local res = lb_[k]
        if res == nil then
            res = 0
        end
        return res
    end,

    __newindex = function(_, _, v)
        local res = lb_[v]
        if res == nil then
            res = 0
        end
        lb_[v] = res + 1
    end,

    __len = function()
        return #lb_
    end
}
setmetatable(lb, mt)
local function read_input()
    local a, b = io.read("*n", "*n")
    while (a ~= nil) do
        la[#la + 1] = a
        lb[#lb + 1] = b
        a, b = io.read("*n", "*n")
    end
end


read_input()
local diff = 0
for _, v in pairs(la) do
    diff = diff + v * lb[v]
end
print("\n\n\n" .. diff)
