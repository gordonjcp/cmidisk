Fairlight CMI disk extractor
============================


Building
--------

Ensure you have libsndfile development headers.  On Ubuntu, you want:

  $ sudo apt-get install libsndfile1-dev

Configure and build:

  $ ./waf configure && ./waf
  
Optionally, install:

  $ sudo ./waf install

Using cmitool
-------------

  $ ./build/cmitool ~/disks/EFFECTS1.IMD

You will now have a whole bunch of .wav files in the directory, extracted
from the Fairlight CMI ImageDisk file.

Using unimd
-----------

  $ ./build/unimd ~/disks/EFFECTS1.IMD
  
or

  $ ./build/unimd ~/disks/EFFECTS1.IMD ~/diskbins/effects1.imd
  
Be careful when specifying an output parameter, because in these early stages
there's pretty much no sanity checking.

Have fun, and make silly noises.

Gordonjcp MM0YEQ
