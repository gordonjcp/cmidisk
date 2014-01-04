Fairlight CMI disk extractor
============================


Building
--------

Ensure you have libsndfile development headers.  On Ubuntu, you want:

  $ sudo apt-get install libsndfile1-dev

Configure and build:

  $ ./waf configure && ./waf

Run:

  $ ./build/cmitool ~/disks/EFFECTS1.IMD

You will now have a whole bunch of .wav files in the directory, extracted from the Fairlight CMI ImageDisk file.

Have fun, and make silly noises.

Gordonjcp MM0YEQ
