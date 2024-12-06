print("AOC 2024 - day 1")
local la = {}
local lb = {}
local function read_input()
    io.input("day1.input")
    local a, b = io.read("*n", "*n")
    while (a ~= nil) do
        la[#la + 1] = a
        lb[#lb + 1] = b
        a, b = io.read("*n", "*n")
    end
end

local function percolate_down(arr, i)
    while (i <= #arr) do
        local min = i * 2

        if min > #arr then
            break
        end

        if min + 1 <= #arr and arr[min + 1] < arr[min] then
            min = min + 1
        end

        if arr[min] > arr[i] then
            break
        end

        arr[i], arr[min] = arr[min], arr[i]
        i = min
    end
end

local function heapify(arr)
    mid = #arr // 2
    for i = mid, 1, -1 do
        percolate_down(arr, i)
    end
end

local function pop(h)
    if #h == 0 then
        return nil
    end
    local res = h[1]
    h[1] = h[#h]
    h[#h] = nil
    percolate_down(h, 1)
    return res
end

read_input()
heapify(la)
heapify(lb)
local diff = 0
for _ = 1, #la do
    diff = diff + math.abs(pop(la) - pop(lb))
end
print(diff)
