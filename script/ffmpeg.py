# python wrapper for basic ffmpeg operations
# resize video, check if a video is corrupted, etc.

import subprocess, re, os

# provide your own ffmpeg here
ffmpeg = 'ffmpeg'

# resize videoName to 320x240 and store in resizedName
# if succeed return True
def resize(videoName, resizedName):
    if not os.path.exists(videoName):
        print '%s does not exist!' % videoName
        return False
    # call ffmpeg and grab its stderr output
    p = subprocess.Popen([ffmpeg, "-i", videoName], stderr=subprocess.PIPE)
    out, err = p.communicate()
    # search resolution info
    if err.find('differs from') > -1:
        return False
    reso = re.findall(r'Video.*, ([0-9]+)x([0-9]+)', err)
    if len(reso) < 1:
        return False
    # call ffmpeg again to resize
    subprocess.call([ffmpeg, '-i', videoName, '-s', '320x240', resizedName])
    return check(resizedName)

# check the video file is corrupted or not
def check(videoName):
    if not os.path.exists(videoName):
        return False
    p = subprocess.Popen([ffmpeg, "-i", videoName], stderr=subprocess.PIPE)
    out, err = p.communicate()
    if err.find('Invalid') > -1:
        return False
    return True

