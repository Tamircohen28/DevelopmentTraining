# to run script you need:
# python 3 and pip3
# from pip you need to install selenium -> pip install -u selenium
# you need to install google chrome
# you need to download chromedriver.exe by you chrome version
# update paths by you pc dirs

from selenium.webdriver.support.ui import WebDriverWait
from selenium.common.exceptions import NoSuchElementException
from selenium import webdriver
import os
from shutil import copy2
import sys
import urllib.request
import urllib.parse
import re
import argparse

# TODO: Make sure you change the path to match your pc
C_DOWNLOAD_PATH = r"C:\Users\Tamir Cohen\Downloads"
C_CHROME_DRIVER_EXE_PATH = r"C:\Users\Tamir Cohen\Downloads\chromedriver_win32\chromedriver.exe"


def create_dir(new_dir):
    """
    this function creates a new dir
    :param new_dir: the new dir
    :return: bool
    """
    if not os.path.exists(new_dir):
        try:
            os.mkdir(new_dir)
            return True

        except OSError:
            print("Creation of the directory %s failed" % new_dir)
            return False

    return True


def delete_path(path):
    """
    this function deletes file
    :param path: file path
    :return: bool
    """
    if os.path.exists(path):
        os.remove(path)
        return True
    else:
        print("The file {0} does not exist and can't be deleted")
        return False


def copy_dir(path, new_dir):
    """
    this function copy a file
    :param path: file path
    :param new_dir: the new file path
    :return: bool
    """
    if os.path.exists(new_dir):
        copy2(path, new_dir)
        return True
    else:
        print("Can't copy path {0} does not exist".format(new_dir))
        return False


def get_last_file(path):
    """
    this function return the last file created in a folder
    :param path: any path
    :return: the newest file
    """
    files = os.listdir(path)
    paths = [os.path.join(path, basename) for basename in files]
    try:
        return max(paths, key=os.path.getctime)
    except ValueError:
        print("{0} does not exist to get_last_file".format(path))


def every_downloads_chrome(driver_obj):
    if not driver_obj.current_url.startswith("chrome://downloads"):
        driver_obj.get("chrome://downloads/")

    return driver_obj.execute_script("""
        var items = downloads.Manager.get().items_;
        if (items.every(e => e.state === "COMPLETE"))
            return items.map(e => e.file_url);
        """)


def download_url(driver_obj, url):
    """
    this function download a url song
    :param driver_obj: a driver object
    :param url: any url of youtube
    :return: None
    """
    # Open the website
    driver_obj.get('https://ytmp3.cc/')

    # Select the id box
    url_box = driver_obj.find_element_by_id('input')

    # Send id information
    url_box.send_keys(url)

    # Find submit button
    submit_button = driver_obj.find_element_by_id('submit')

    # Click login
    submit_button.click()
    print("Waiting for load to finish...")

    # trying to download until is succeed
    while True:
        try:
            # Find download button
            download_button = driver_obj.find_element_by_link_text("Download")
            break
        except NoSuchElementException:
            pass

    print("Load had finished, Downloading the song...")
    # Click download
    download_button.click()
    print("Waiting for download...")

    # waiting for download to end
    WebDriverWait(driver_obj, 120, 1).until(every_downloads_chrome)
    print("Download had finished!")

    # closing window
    driver_obj.close()


def get_optional_url(search):
    """
    this function returns the list of possible urls for search of song
    in youtube
    :param search: the song name to search
    :return: list of url
    """
    query_string = urllib.parse.urlencode({"search_query": search})
    html_content = urllib.request.urlopen("http://www.youtube.com/results?" + query_string)
    search_results = re.findall(r'href=\"\/watch\?v=(.{11})', html_content.read().decode())

    # casting double searches
    results = []
    for i in range(len(search_results)):
        # getting the current search
        current_search = "http://www.youtube.com/watch?v=" + search_results[i]
        if current_search not in results:
            results.append(current_search)

    return results


def user_pick_song(driver_obj, list_of_url, num_of_pick):
    """
    this function shows thw user the url and ask if he wants to download it
    :param driver_obj: the driver object
    :param list_of_url: list of url to compare
    :param num_of_pick: num of picks to let the user chose
    :return: url chosen
    """
    for i in range(num_of_pick):
        try:
            print("\n$ Showing {0}".format(list_of_url[i]))
            # showing the page
            driver_obj.get(list_of_url[i])
            result = input("Is this the song you wanted? press 1 for confirm or enter to go on\n")

            if result == "1":
                driver_obj.close()
                return list_of_url[i]

        except IndexError:
            print("length of url list was {0} and you didn't chose anything".format(len(list_of_url)))
            return ""

    driver_obj.close()
    print("You didn't chose anything in the given options...")
    return ""


def download_song(search, output_path, filling_lucky, list_of_songs, quite, list_of_url):
    """
    this function downloads a song from youtube to a given dir
    :param search: the name of song to search
    :param output_path: the output path of the download path
    :param filling_lucky: bool, if to lat to program chose the url alone or user chose
    :param list_of_songs: list of url's the user want to download
    :param quite: turn off song page open
    :return: None
    """

    song_url = []
    if len(list_of_songs) == 0 and search != "":
        # possible url
        list_of_url = get_optional_url(search)
        if filling_lucky:
            song_url = [list_of_url[0]]
        else:
            # Using Chrome to access web
            driver = webdriver.Chrome(C_CHROME_DRIVER_EXE_PATH)
            song_url = [user_pick_song(driver, list_of_url, len(list_of_url))]

            if song_url == "":
                sys.exit("\n** No url was chose")

    elif len(list_of_songs) > 0:
        print("\n@@@ Downloading user costume list of songs @@@")
        for song in list_of_songs:
            song_url.append(get_optional_url(song)[0])

    if len(list_of_url) > 0:
        print("\n$$$ Downloading user costume list of url $$$")

    for url in song_url + list_of_url:
        driver2 = webdriver.Chrome(C_CHROME_DRIVER_EXE_PATH)

        if not quite:
                temp_driver = webdriver.Chrome(C_CHROME_DRIVER_EXE_PATH)

        try:
            print("\n### Downloading song from {0} ###".format(url))

            # show song page
            if not quite:
                temp_driver.get(url)

            # downloading the url
            download_url(driver2, url)

            # getting the newest file from download list
            file_path = get_last_file(C_DOWNLOAD_PATH).replace("\\", "/")

            if not create_dir(output_path):
                driver2.close()
                sys.exit("can't create new dir, song is in {0}".format(file_path))

            # copying new dir
            if copy_dir(file_path, output_path):
                file_path_out = output_path
                # delete old dir
                delete_path(file_path)

            else:
                file_path_out = file_path

            if not quite:
                temp_driver.close()

            print("\n$$ Song file is waiting for you in {0}!".format(file_path_out))

        except PermissionError:
            if not quite:
                temp_driver.close()
            sys.exit('Error occur, check destination and download paths')


if __name__ == '__main__':
    ap = argparse.ArgumentParser()
    ap.add_argument("-d", "--des", required=True, dest='dest_path',
                    action='store', help="the destination folder")
    ap.add_argument("-fu", "--file_url", required=False, dest='url_file_path',
                    action='store', help="txt file with url list")
    ap.add_argument("-fs", "--file_song", required=False, dest='songs_file_path',
                    action='store', help="txt file with songs list")
    ap.add_argument("-u", "--user", required=False, dest="user_pick",
                    action='store_true', default=False, help="use if you want to chose the file yourself")
    ap.add_argument("-s", "--search", required=True, dest="search",
                    action='store', help="the search wanted")
    ap.add_argument("-q", "--quite", required=False, dest="quite",
                    action='store_true', default=False, help="turn off youtube page opening")

    parser = ap.parse_args()

    list_of_songs = []
    # checking if to use a url file
    if parser.songs_file_path is not None:
        with open(parser.songs_file_path, 'r') as songs_file:
            for line in songs_file:
                check = line.replace("\n", "")
                if check not in list_of_songs and check != "":
                    list_of_songs.append(check)

    list_of_urls = []
    # checking if to use a url file
    if parser.url_file_path is not None:
        with open(parser.url_file_path, 'r') as url_file:
            for line in url_file:
                check = line.replace("\n", "")
                if check not in list_of_urls and check != "":
                    list_of_urls.append(check)

    download_song(parser.search, parser.dest_path, not parser.user_pick, list_of_songs, parser.quite, list_of_urls)
