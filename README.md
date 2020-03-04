![Logo](docs/media/LittleCallisto.png "Callisto")


Callisto
========

Core C++ libraries.



## NervNet Sim Tools

#### Make_Network

    USAGE: make_network options
    
    required:
      net	- network config file


#### Train Network

    USAGE: train_network options
    
    required:
      old	- old network config file
      new	- new network config file
      trn	- training exemplars
      epc	- number of epochs [default: 1000]
      bat	- batch size (percent of training data) [default: 10%]
      rpt	- number of epochs between reports [default: 100]
      eta	- training coefficient [default: 0.09]
    optional:
      tst	- testing exemplars
    

#### Execute Network

    USAGE: callisto/bin/execute_network options

    required:
      net   - network config file
      if    - input file (if labels exist they are ignored)
      of    - output file (input and output written as a pair)
    optional:
      fmt   - label file input  format (default: %23.16e)
      ofmt  - label file output format (default: same as fmt)

#### Validate Network

    USAGE: callisto/bin/validate_network options

    options
    required:
      tru	- path to ground truthed exemplar file
      tst	- path to exemplar file to be tested
    optional:
      rpt	- path to report file 1=stdout, 2=stderr

## Run a Test Group

First make the training and testing data sets.

    >> ../scripts/MakeIrisExemplar.sh
    
    >>


next, make neural network. (***note:*** input/outputs must be 4/3 for the Iris dataset)

    >> callisto/bin/make_network net=iris_rnd.net
    Number of inputs:  4
    Number of outputs: 3
    Number of layers:  3
      Hidden layer 1 [12]: 8
      Hidden layer 2 [5]:  6

    Current Network Configuration
    -----------------------------

    Number of Inputs:  4
    Hidden layer 1:    8
    Hidden layer 2:    6
    Number of Outputs: 3

    Are these values correct(y/n): y
    
    >>

next, train the network

    >> callisto/bin/train_network old=iris_rnd.net new=iris.net trn=iris_train.exm tst=iris_test.exm epc=20000 rpt=5000 bat=90 eta=0.09
    
      0 0.8773
     10 0.6429
     20 0.5651
     30 0.5811
     40 0.5323
     50 0.4451
     60 0.3828
     70 0.2576
     80 0.0923
     90 0.0017
    100 0.0011
    
    Elapsed training: 0.01435 seconds
    
    >>

next, use the network to label unlabeled data. 

    >> callisto/bin/execute_network net=iris.net if=iris_unlabeled.exm of=iris_labeled.exm fmt="%5.2f" ofmt="%7.4f"
    
finally, let us run a validation report on the network.

    >> callisto/bin/validate_network tru=iris_train.exm tst=iris_labeled.exm rpt=report.txt
