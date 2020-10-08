class Node():
    """A node class for A* Pathfinding"""

    def __init__(self, parent=None, position=None):
        self.parent = parent
        self.position = position

        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.position == other.position


def astar(maze, start, end):
    """Returns a list of tuples as a path from the given start to the given end in the given maze"""

    # Create start and end node
    start_node = Node(None, start)
    start_node.g = start_node.h = start_node.f = 0
    end_node = Node(None, end)
    end_node.g = end_node.h = end_node.f = 0

    # Initialize both open and closed list
    open_list = []
    closed_list = []

    # Add the start node
    open_list.append(start_node)

    # Loop until you find the end
    while len(open_list) > 0:

        # Get the current node
        current_node = open_list[0]
        current_index = 0
        for index, item in enumerate(open_list):
            if item.f < current_node.f:
                current_node = item
                current_index = index

        # Pop current off open list, add to closed list
        open_list.pop(current_index)
        closed_list.append(current_node)

        # Found the goal
        if current_node == end_node:
            path = []
            current = current_node
            while current is not None:
                path.append(current.position)
                current = current.parent
            return path[::-1] # Return reversed path

        # Generate children
        children = []
        for new_position in [(0, -1), (0, 1), (-1, 0), (1, 0), (-1, -1), (-1, 1), (1, -1), (1, 1)]: # Adjacent squares

            # Get node position
            node_position = (current_node.position[0] + new_position[0], current_node.position[1] + new_position[1])

            # Make sure within range
            if node_position[0] > (len(maze) - 1) or node_position[0] < 0 or node_position[1] > (len(maze[len(maze)-1]) -1) or node_position[1] < 0:
                continue

            # Make sure walkable terrain
            if maze[node_position[0]][node_position[1]] != 0:
                continue

            # Create new node
            new_node = Node(current_node, node_position)

            # Append
            children.append(new_node)

        # Loop through children
        for child in children:

            # Child is on the closed list
            for closed_child in closed_list:
                if child == closed_child:
                    continue

            # Create the f, g, and h values
            child.g = current_node.g + 1
            child.h = ((child.position[0] - end_node.position[0]) ** 2) + ((child.position[1] - end_node.position[1]) ** 2)
            child.f = child.g + child.h

            # Child is already in the open list
            for open_node in open_list:
                if child == open_node and child.g > open_node.g:
                    continue

            # Add the child to the open list
            open_list.append(child)


def main():
    import cv2 as cv
    import numpy as np
    import matplotlib.pyplot as plt 
    
    # Treating the image
    mapa = cv.imread("mapa.bmp")
    cv.imshow("Original map", mapa)
    mapa_copy = cv.imread("mapa.bmp", 0) # To perform transformations, already grayscale
    
    #Binarizing map, first we force 255 to any value higher than 0
    ret, mapa_copy = cv.threshold(mapa_copy, 0, 255, cv.THRESH_BINARY_INV)
    mapaBinario = mapa_copy // 255 # Then we divine by 255, so we have 0s and 1s
    
    resolucaoAStar = 5 #Used for proportion of AStar cells
    
    # Creating a new matrix with zeros and cell(grid) resolution.
    size = int(mapaBinario.shape[0]/resolucaoAStar), int(mapaBinario.shape[1]/resolucaoAStar)
    mapaCells = np.zeros(size, dtype=np.uint8)
    
    for (i, m) in zip(range(mapaCells.shape[0]), range(0 , mapaBinario.shape[0] +1, 5)):
        for (j, n) in zip(range(mapaCells.shape[1]), range(0 , mapaBinario.shape[1] +1, 5)):
            mapaCells[i, j] = mapaBinario[m, n]
    
    
    fileName = 'mapaCells.bmp'
    #cv.imwrite("mapaCells.bmp", mapaCells)
    
    img_rgb = cv.imread(fileName)
    
            # altura, largura
    #start = (43, 67)
    #end = (64, 42)
    
    #start = (70, 88)
    #end = (66, 3)
    
    start = (13, 3)
    end = (13, 25)

    path = astar(mapaCells, start, end)

    for pixel in path:
        img_rgb[pixel[0]][pixel[1]] = (0, 0, 255)
    
    
    # In order to show the path we selected only the color channel we painted 
    # in img_rgb, and painted a red 3x3 square.
    for (i, m) in zip(range(img_rgb.shape[0]), range(0 , 1 + mapa.shape[0], 5)):
        for(j, n) in zip(range(img_rgb.shape[1]), range(0, 1 + mapa.shape[1], 5)):
            if((img_rgb[i,j,1]==0) and (img_rgb[i,j,0]==0) and (img_rgb[i,j,2]==255)):
                mapa[m-1, n-1] = img_rgb[i, j]
                mapa[m, n-1] = img_rgb[i, j]
                mapa[m+1, n-1] = img_rgb[i, j]
                mapa[m+1, n] = img_rgb[i, j]
                mapa[m, n] = img_rgb[i, j]
                mapa[m-1, n] = img_rgb[i, j]
                mapa[m-1, n+1] = img_rgb[i, j]
                mapa[m, n+1] = img_rgb[i, j]
                mapa[m+1, n+1] = img_rgb[i, j]
    
    #Because opencv reads bgr and matplotlib default is rgb the trajectory
    #color may be different.
    plt.imshow(mapa,extent=(0, 9, 0, 7.2))
    plt.show()
    
    #cv.imwrite("Trajectorymap.bmp", mapa)
    cv.imshow("Trajectory map", mapa)
    cv.waitKey(0)


if __name__ == '__main__':
    main()
