def find_best_paths(grid):
    # Parse input grid
    start = find_start(grid)
    end = find_end(grid)
    
    # State: (x, y, direction, cost)
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]  # East, South, West, North
    best_costs = {}  # To track minimum cost to reach each (x, y, direction)
    queue = PriorityQueue()  # Use a priority queue for Dijkstra's

    # Initialize
    queue.put((0, start[0], start[1], 0))  # cost, x, y, direction (East)
    best_costs[(start[0], start[1], 0)] = 0

    # Dijkstra's algorithm
    while not queue.empty():
        cost, x, y, dir_idx = queue.get()

        # Skip if not optimal
        if best_costs.get((x, y, dir_idx), float('inf')) < cost:
            continue

        # Move forward
        nx, ny = x + directions[dir_idx][0], y + directions[dir_idx][1]
        if is_valid(nx, ny, grid):
            forward_cost = cost + 1
            if forward_cost < best_costs.get((nx, ny, dir_idx), float('inf')):
                best_costs[(nx, ny, dir_idx)] = forward_cost
                queue.put((forward_cost, nx, ny, dir_idx))

        # Rotate (clockwise and counterclockwise)
        for turn in [-1, 1]:
            new_dir_idx = (dir_idx + turn) % 4
            rotate_cost = cost + 1000
            if rotate_cost < best_costs.get((x, y, new_dir_idx), float('inf')):
                best_costs[(x, y, new_dir_idx)] = rotate_cost
                queue.put((rotate_cost, x, y, new_dir_idx))

    # Find all tiles in best paths
    best_score = min(best_costs[(end[0], end[1], d)] for d in range(4))
    best_tiles = set()
    for (x, y, d), cost in best_costs.items():
        if cost == best_score:
            best_tiles.add((x, y))
    
    return len(best_tiles)

