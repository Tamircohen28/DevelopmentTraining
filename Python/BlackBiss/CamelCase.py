# python 3.5.2
# Tamir Cohen 17/03/2020


def break_camel(text):
    """
    function
    :param text:
    :return:
    """
    return ''.join([" " + char if char.isupper() else char for char in text])
