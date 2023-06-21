import time

def possible(grid, x, y, n):
    
    """

    grid: Tablero del Sudoku
    x : Indice de Fila [0-8]
    y : Indice de Columna [0-8]
    n : Numero a colocar en el tablero [1-9] 
    
    Returns: True si es posible colocar n en la posicion (x,y) del tablero

    """

    # Verifica que n no pertenece a la fila x
    for i in range(0,9):
        if grid[x][i] == n:
            return False

    # Verifica que n no pertenece a la fila y
    for i in range(0,9):
        if grid[i][y] == n:
            return False

    # Verifica que n no pertenece a la submatriz de 3x3 que le corresponde
    xo = (x//3) * 3
    yo = (y//3) * 3
    for i in range(0, 3):
        for j in range(0, 3):
            if grid[xo+i][yo+j] == n:
                return False

    return True


def is_full(grid):
    
    """

    grid: Tablero de 9x9      
    Returns: True si el sudoku esta lleno
    
    """

    for i in range(9):
        for j in range(9):
            if(grid[i][j] == 0):
                return False
    return True


def print_sudoku(grid):
        
        """
    
        grid: Tablero de 9x9      
        Returns: Imprime el tablero de forma legible
    
        """
    
        for i in range(9):
            for j in range(9):
                print(grid[i][j], end = " ")
            print()


def dfs(grid, col, fil):
    if(col == 9):
        col = 0
        fil += 1
    
    if(fil == 9):
        return True
    
    if(grid[fil][col] > 0):
        return dfs(grid, col+1, fil)
    
    for num in range(1, 9 + 1, 1):
        if possible(grid, fil, col, num):
            grid[fil][col] = num
            if dfs(grid, col+1, fil):
                return True
        grid[fil][col] = 0

    return False

def solve(grid):

    """ Resuelve un sudoku de 9x9.

    Args:
        grid: Tablero de 9x9. Las casillas vacias se representan con 0.

    Returns:
        grid: El tablero resuelto.

    """
    dfs(grid, 0, 0)
    return grid

grid = [
[5, 3, 0, 0, 7, 0, 0, 0, 0],
[6, 0, 0, 1, 9, 5, 0, 0, 0],
[0, 9, 8, 0, 0, 0, 0, 6, 0],
[8, 0, 0, 0, 6, 0, 0, 0, 3],
[4, 0, 0, 8, 0, 3, 0, 0, 1],
[7, 0, 0, 0, 2, 0, 0, 0, 6],
[0, 6, 0, 0, 0, 0, 2, 8, 0],
[0, 0, 0, 4, 1, 9, 0, 0, 5],
[0, 0, 0, 0, 8, 0, 0, 7, 9]]

grid2 = [
[0, 0, 6, 0, 0, 0, 0, 0, 0],
[0, 5, 0, 4, 0, 0, 0, 0, 6],
[0, 0, 0, 7, 0, 0, 2, 4, 9],
[9, 0, 0, 0, 0, 0, 0, 1, 0],
[8, 0, 0, 0, 0, 0, 0, 0, 3],
[0, 3, 1, 0, 0, 0, 4, 7, 0],
[5, 8, 0, 3, 0, 4, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 9, 0, 0],
[7, 0, 0, 0, 5, 8, 0, 0, 0]]

def main():
    print("Sudoku DFS")
    inicio = time.time()
    grid3=solve(grid2)
    fin = time.time()
    print("Tiempo de ejecucion: ", fin-inicio)
    print_sudoku(grid3)

main()

