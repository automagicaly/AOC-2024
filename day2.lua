local function read_list(line)
    local res = {}
    for v in string.gmatch(line, "%d+") do
        res[#res + 1] = math.tointeger(v)
    end
    return res
end
local function read_input()
    io.input("day2.input")
    local lists = {}
    for l in io.lines() do
        if l == nil or string.len(l) == 0 then
            break
        end
        lists[#lists + 1] = read_list(l)
    end
    return lists
end

local function print_list(l)
    local s = ""
    for k, v in ipairs(l) do
        s = s .. k .. ":" .. tostring(v) .. " "
    end
    print(s)
end

local function is_safe_report(r)
    local last = r[1]
    local dir = nil
    local is_safe = true
    for _, v in pairs({ table.unpack(r, 2) }) do
        local diff = v - last
        local new_dir = diff / math.abs(diff)
        diff = math.abs(diff)
        if dir == nil then
            dir = new_dir
        end
        if diff < 1 or diff > 3 or dir ~= new_dir then
            is_safe = false
            break
        end
        last = v
    end
    return is_safe
end

local safe = 0
local lists = read_input()
for _, r in ipairs(lists) do
    if is_safe_report(r) then
        safe = safe + 1
    end
end
print("AOC 2024 - day 2")
print(safe)
