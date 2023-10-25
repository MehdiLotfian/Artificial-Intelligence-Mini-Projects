result = False


def are_children_occurred(current_node, direct, occurred, observed):
    global result
    if occurred[current_node]:
        result = True
    if current_node in observed:
        return
    observed.add(current_node)
    for node in direct[current_node]:
        if not result:
            are_children_occurred(node, direct, occurred, observed)


def find_active_path(current_node, final_node, direct, indirect, occurred, observed, path, is_first, is_direct):
    global result
    result = False
    if current_node == final_node:
        path.append(current_node)
        return path
    if current_node in observed:
        return path
    observed.add(current_node)
    path.append(current_node)
    new_path = path.copy()
    if is_first or (not occurred[current_node]):
        for node in direct[current_node]:
            if len(new_path) == 0 or new_path[-1] != final_node:
                new_path = find_active_path(node, final_node, direct, indirect, occurred, observed, path, False, True)
    are_children_occurred(current_node, direct, occurred, set())
    if is_first or (is_direct and result) or (not is_direct and not occurred[current_node]):
        for node in indirect[current_node]:
            if len(new_path) == 0 or new_path[-1] != final_node:
                new_path = find_active_path(node, final_node, direct, indirect, occurred, observed, path, False, False)
    if new_path[-1] == final_node:
        return new_path
    observed.discard(current_node)
    if current_node in new_path:
        new_path.remove(current_node)
    if current_node in path:
        path.remove(current_node)
    return new_path


if __name__ == '__main__':
    nmz = [int(i) for i in input().strip().split()]
    direct = []
    indirect = []
    occurred = [False] * (nmz[0] + 1)
    for _ in range(nmz[0] + 1):
        direct.append(set())
        indirect.append(set())
    for _ in range(nmz[1]):
        ab = [int(i) for i in input().strip().split()]
        direct[ab[0]].add(ab[1])
        indirect[ab[1]].add(ab[0])
    for _ in range(nmz[2]):
        occurred[int(input().strip())] = True
    target_nodes = [int(i) for i in input().strip().split()]
    final_path = find_active_path(target_nodes[0], target_nodes[1], direct, indirect, occurred, set(), list(), True,
                                  False)
    if len(final_path) != 0 and final_path[-1] == target_nodes[1]:
        print(', '.join(list(map(str, final_path))))
    else:
        print("independent")
