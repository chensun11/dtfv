# extract DT features on the fly and select feature points randomly
# need select_pts and dt binaries

import subprocess, os, ffmpeg
import sys

# Dense Trajectories binary
dtBin = './DenseTrackStab'
# Compiled fisher vector binary
fvBin = './compute_fv'
# Temp directory to store resized videos
tmpDir = '/tmp'
# Process ID for running in parallel
pID = 0
# PCA list
pcaList = '../data/med.pca.lst'
# GMM list
codeBookList = '../data/med.codebook.lst'

def extract(videoName, outputBase):
    if not os.path.exists(videoName):
        print '%s does not exist!' % videoName
        return False
    if check_dup(outputBase):
        print '%s processed' % videoName
        return True
    resizedName = os.path.join(tmpDir, os.path.basename(videoName))
    if not ffmpeg.resize(videoName, resizedName):
        resizedName = videoName     # resize failed, just use the input video
    subprocess.call('%s %s | %s %s %s %s' % (dtBin, resizedName, fvBin, pcaList, codeBookList, outputBase), shell=True)
    return True

def check_dup(outputBase):
    """
    Check if fv of all modalities have been extracted
    """
    featTypes = ['traj', 'hog', 'hof', 'mbhx', 'mbhy']
    featDims = [20, 48, 54, 48, 48]
    for i in range(len(featTypes)):
        featName = '%s.%s.fv.txt' % (outputBase, featTypes[i])
        if not os.path.isfile(featName) or not os.path.getsize(featName) > 0:
            return False
        # check if the length of feature can be fully divided by featDims
        f = open(featName)
        featLen = len(f.readline().rstrip().split())
        f.close()
        if featLen % (featDims[i] * 512) > 0:
            return False
    return True

if __name__ == '__main__':
    videoList = sys.argv[1]
    outputBase = sys.argv[2]
    totalTasks = int(sys.argv[3])
    try:
        f = open(videoList, 'r')
        videos = f.readlines()
        f.close()
        videos = [video.rstrip() for video in videos]
        for i in range(0, len(videos)):
            if i % totalTasks == int(pID):
                print pID, videos[i]
                outputName = os.path.join(outputBase, os.path.basename(videos[i]))
                extract(videos[i], outputName)
    except IOError:
        sys.exit(0)
