x_a, y_a = map(int, input().split())
x_b, y_b = map(int, input().split())
x_c, y_c = map(int, input().split())


def is_right_triangle(xA, yA, xB, yB, xC, yC):
    ABx, ABy = xB - xA, yB - yA
    BCx, BCy = xC - xB, yC - yB
    CAx, CAy = xA - xC, yA - yC

    dot_AB_BC = ABx * BCx + ABy * BCy
    dot_BC_CA = BCx * CAx + BCy * CAy
    dot_CA_AB = CAx * ABx + CAy * ABy

    if dot_AB_BC == 0 or dot_BC_CA == 0 or dot_CA_AB == 0:
        return True
    return False


if is_right_triangle(x_a, y_a, x_b, y_b, x_c, y_c):
    print('Yes')
else:
    print('No')
