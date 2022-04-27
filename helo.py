position_list = [(0,0,0),
                 (1,0,0),
                 (2,0,0),
                 (0,1,0),
                 (2,1,0),
                 (0,2,0),
                 (1,2,0),
                 (2,2,0),
                 (0,0,1),
                 (2,0,1),
                 (0,2,1),
                 (2,2,1),
                 (0,0,2),
                 (1,0,2),
                 (2,0,2),
                 (0,1,2),
                 (2,1,2),
                 (0,2,2),
                 (1,2,2),
                 (2,2,2)]
cube_list = list()
cube_list.append((2,2,0))
cube_list.append((2,2,2))
for cube in cube_list:
    if cube in [position for position in position_list]:
        print("HOI")