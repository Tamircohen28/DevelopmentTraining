# python 3.5.2
# Tamir Cohen 17/03/2020


def word_contained(str_a, str_b):
    """
    this function check if all the letters in str_a are contained in str_b
    :return: bool
    """
    return all([char in str_b for char in str_a])


def dejumble(scramble_word, optional_list):
    """
    function returns possible list of word the the pirates said
    :param scramble_word: string
    :param optional_list: list of string
    :return: list of string
    """
    return list(filter(None, [option if word_contained(option, scramble_word) and word_contained(scramble_word, option)
                and len(option) == len(scramble_word) else None for option in optional_list]))


if __name__ == '__main__':
    print(dejumble("ortsp", ['sport', 'parrot', 'ports', 'amsa']))
