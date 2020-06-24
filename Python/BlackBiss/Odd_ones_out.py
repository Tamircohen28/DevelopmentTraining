# python 3.5.2
# Tamir Cohen 17/03/2020


def odd_ones_out(numbers):
    """
    remove odd numbers from list
    :param numbers: list of int
    :return: list of even int
    """

    return list(filter(None, [num if num % 2 == 0 else None for num in numbers]))
