=====
Fisher Vector implementation for Dense Trajectories (DTFV)
=====

This is a C++ implementation of Fisher Vector (FV) for Dense Trajectory (DT) features.

DTFV provides a binary with a Python script to generate Fisher Vectors. It also provides code to sample feature points, and to train PCA and GMM codebooks.

Some highlights include:

* Provides a full pipeline from DT raw feature to Fisher Vectors

* Aggregate feature points on-the-fly, no need to load all points in memory

* Raw features are piped to the Fisher Vector generator, no need to store the large raw features

* State-of-the-art performance for large action/event video datasets

It depends on:

* Dense Trajectories (DT_)
    To extract DT features
* VLFeat_
    To train Gaussian Mixture Models
* ALGLIB_
    To train PCA projection matrix

Using linear SVM, we tested the code on two action/event classification datasets:

* TRECVID Multimedia Event Detection (MED_)
    Trained on EX100, tested on MEDTest. The mean average precision for event 6 to 15 and 21 to 30 is 0.33.
* UCF 101
    Partitions were defined by THUMOS_ workshop. The average classification accuracy is 85%.

The pretrained codebooks on these two dataset are also provided.

Please see our WACV_ 2013 paper for more details.

.. _ALGLIB: http://www.alglib.net/
.. _VLFeat: http://www.vlfeat.org/
.. _DT: https://lear.inrialpes.fr/people/wang/improved_trajectories
.. _MED: http://www-nlpir.nist.gov/projects/tv2013/tv2013.html#med
.. _THUMOS: http://crcv.ucf.edu/ICCV13-Action-Workshop/
.. _WACV: http://www-scf.usc.edu/~chensun/
