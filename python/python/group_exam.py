# coding=utf-8
'''
Exam requests: 
Write a class PostcardList that satisfies the tests (defined using unittest).
 
SPECIFICATIONS: 
- Class PostcardList reads/writes Postcard messages from/to a properly 
  formatted file: each record (i.e., file's line) is a Postcard. 
- The Postcard format is "date:$(DATE); from:$(SENDER); to:$(RECEIVER);" 
  (e.g., "date:2009-12-24; from:Daisy; to:Donald;"). 
- Class PostcardList must manage the I/O file using:
  (1) writeFile(self,...)
  (2) readFile(self,...)
  (3) parsePostcards(self,...) 
  (4) updateFile(self,...)
  (5) updateLists(self,...)
  (6) getNumberOfPostcards(self)
- Class PostcardList must manage the sorting of dates/senders/receivers using: 
  (7) getPostcardsByDateRange(self,date_range): returns the postcards within 
      a date_range
  (8) getPostcardsBySender(self, sender): returns the postcards from a sender
  (9) getPostcardsByReceiver(self, receiver): returns the postcards to a receiver
'''
import unittest
import datetime # module to deal with dates

# ************************* Class for Postcard List *************************
class PostcardList(object): 
    def __init__ (self, postcards = None): # I can give the arguments with keywords
    # class constructor:
    # - the "self" variable: instance of the object itself 
    # - when calling PostcardList(), Py creates an object and passes it as
    #   the first parameter to the __init__ method.
    # Initialization:
    # - None => string
    # - [] => list
    # - {} => dictionary (data structure mapping 1 value to another)
        self._file = None # file name
        if postcards is None: #None è oggetto speciale cm True o false
           self._postcards = []
        else:
           self._postcards = postcards
        self._date = {} # key: string date; value: list of indices
        self._from = {} # key: string sender; value: list of indices
        self._to = {}  # key: string receiver; value: list of indices

# ------------------------- Functions for I/O -------------------------
    def writeFile(self): # (1)
    # write self.{_date,_from,_to} to self._file
# http://www.pythonforbeginners.com/files/reading-and-writing-files-in-python
        with open(self._file,'w') as f:
            for postcard in self._postcards:
                f.write(str(postcard))
                # str: string to be written in the file
                
    def readFile(self,filename): # (2)
    # read from self._file read self.{_date,_from,_to}
        with open(filename) as f:
            #read is the default of open so I do not need to write ,'r' .
            for line in f:
                self._postcards.append(line)
            self._file = filename
        self.parsePostcards()

    def parsePostcards(self): # (3)
    # parse self._postcards, set self.{_date,_from,_to}
        for i, postcard in enumerate(self._postcards):
            parts = postcard.split(';')
            pp_date = parts[0].split(':')[1].strip()#; print(pp_date)
            # strip: delete blanks before and after
            # print(pp_date[5:]) => the first 5 elements in a row + all rows
            # print(pp_date[:5]) => all the elements but at max 5 columns
            # print(pp_date[0:2]) => the first 2 elements of all rows
            pp_from = parts[1].split(':')[1].strip()#; print(pp_from)
            pp_to = parts[2].split(':')[1].strip()#; print(pp_to)

            if pp_date not in self._date:
                self._date.update({pp_date: []})
                # if the key already exists, it updates the correspondent value
                # otherwise it adds the new (key; value) pair.
    # https://www.programiz.com/python-programming/methods/dictionary/update
            if pp_from not in self._from:
                self._from.update({pp_from: []})
            if pp_to not in self._to:
                self._to.update({pp_to: []})
                   
            self._date[pp_date].append(i)
            self._from[pp_from].append(i)
            self._to[pp_to].append(i)

    def updateFile(self): # (4)
        # as write but appending to self._file 
            with open(self._file,'a') as f:
                for postcard in self._postcards:
                    f.write(str(postcard))

    def updateLists(self,file2read): # (5)
    # - as read but appending to self._postcards
    # - updates the list of the postcards
    # - initializes the dictionary attributes of the class (key,value)
          self._date = {}
          self._from = {}
          self._to = {}
          self.readFile(file2read)

# -------------------------  Functions for Sorting -------------------------
    def  getPostcardsBySender(self, sender): #(8)
        postcards_sender = []
        if sender in self._from:
            for from_sender in sorted(self._from[sender]):
                postcards_sender.extend([self._postcards[from_sender]])
        return postcards_sender  
      

    def  getPostcardsByReceiver(self, receiver): #(9) same as sender changing from with to
        postcards_receiver = []
        if receiver in self._to:
            for to_receiver in sorted(self._to[receiver]):
                postcards_receiver.extend([self._postcards[to_receiver]])
        return postcards_receiver


    def getNumberOfPostcards(self): #(6)
        return len(self._postcards) #len returns the length of a list
        

#select postcards le seleziona in base al dizionario (7)
    def getPostcardsByDateRange (self, date_range):
        day_postcards = []
        for day in self._date:
           date = datetime.datetime.strptime(day, "%Y-%m-%d")
           if date_range[0] <= date <=date_range[1]:
            day_postcards.extend([self._postcards[i] for i in self._date[day]]) #extend is faster and better than append
        return day_postcards

'''
if statement calling main()
-------------------- Advantages --------------------
- code will be cleaner, easier to read, and better organized
- we can make Python behave like other languages, so more familiar for people
- it will be possible to import that python code as a module
  without nasty side-effects, and so
 - it will be possible to run tests against that code
 - we can import that code into an interactive python shell
   and test/debug/run it

-------------------- Disadvantages --------------------
 Variables inside def main are local, while those outside it are global.
 This may introduce a few bugs and unexpected behaviors.
'''
def main():
    postcards = PostcardList()
    postcards.readFile('exam_postcard_list0.txt')
    print(postcards._file)
    
# ************************* Class for Unit tests *************************
class Test(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self._files = ['./exam_postcard_list{}.txt'.format(i) \
                           for i in range(10)]
        self._PstLst = [PostcardList() for f in self._files]
        [p.readFile(f) for f,p in zip(self._files,self._PstLst)]

    def test_missing_attributes(self): 
        attributes_to_define = ['_file','_postcards','_from','_to',\
                                'writeFile','readFile',\
                                'parsePostcards',\
                                'updateFile','updateLists',\
                                'getPostcardsBySender',\
                                'getNumberOfPostcards',\
                                'getPostcardsByDateRange',\
                                'getPostcardsByReceiver']
        
        for attr in attributes_to_define:
            if attr not in dir(self._PstLst[0]): 
                raise Exception(attr+' is missing')

    def test_check_getPostcardByDateRange(self):
        dr_test = []
        for i in [0,1,4,6]:
            dr_test.append(\
                self._PstLst[i].getPostcardsByDateRange(date_range=\
                   (datetime.datetime.strptime('2008-1-1', "%Y-%m-%d"),\
                    datetime.datetime.strptime('2010-12-31', "%Y-%m-%d"))))
        self.assertListEqual(sorted(dr_test[0]),sorted(['date:2010-06-23; from:Sneezy; to:Alice;\n', 'date:2009-12-12; from:Dopey; to:Peter;\n', 'date:2008-03-23; from:Sneezy; to:Pluto;\n', 'date:2008-06-03; from:Goofy; to:Pluto;\n']))
        self.assertEqual(len(dr_test[1]),1)
        self.assertListEqual(sorted(dr_test[2]),sorted(['date:2010-03-30; from:Louie; to:Sneezy;\n', 'date:2010-03-05; from:Goofy; to:Dopey;\n', 'date:2009-11-08; from:Daisy; to:Minnie;\n', 'date:2010-07-13; from:Bashful; to:Louie;\n', 'date:2008-06-29; from:Huey; to:Dopey;\n', 'date:2009-01-04; from:Alice; to:Hook;\n', 'date:2009-04-28; from:Bashful; to:Mickey;\n']))
        self.assertEqual(len(dr_test[3]),7)

    def test_check_getPostcardBySender(self):
        s_test = []
        for i in [2,3,5,7]:
            for sender in ['Daisy','Bashful','Peter']:
                s_test.append(\
                    self._PstLst[i].getPostcardsBySender(sender=sender))
        self.assertIn('date:2011-12-11; from:Daisy; to:Goofy;\n',s_test[0])
        self.assertListEqual(s_test[1],[])
        self.assertEqual(len(s_test[2]),1)
        self.assertEqual(len(s_test[5]),0)
        self.assertGreater(len(s_test[8]),len(s_test[9]))
        
    def test_check_getPostcardByReceiver(self):
        r_test = []
        for i in [0,3,8,9]:
            for receiver in ['Peter','Hook','Alice','SnowWhite']:
                r_test.append(\
                  self._PstLst[i].getPostcardsByReceiver(receiver=receiver))
        self.assertIn('date:2009-12-12; from:Dopey; to:Peter;\n',r_test[0])
        self.assertListEqual(r_test[1],['date:2016-10-23; from:Sneezy; to:Hook;\n'])
        self.assertEqual(len(r_test[2]),2)
        self.assertEqual(len(r_test[6]),3)

    def test_check_sent_received_when(self): 
        srw_test = []
        for ii in range(10):
            for jj in ["Mickey","Minnie","Goofy","Pluto","Donald","Daisy",\
                       "$crooge","Huey","Dewey","Louie","Peter","Hook","Alice",\
                       "SnowWhite","Doc","Sleepy","Sneezy","Bashful","Dopey",\
                       "Happy","Grumpy"]:
                try:
                    srw_test.append(self._PstLst[ii]._from[jj])
                    srw_test.append(self._PstLst[ii]._to[jj])
                    srw_test.append(self._PstLst[ii]._date[jj])
                except: pass
        self.assertListEqual(srw_test[0],[1])
        self.assertListEqual(srw_test[130],[14,25])
        self.assertListEqual(srw_test[138],[10])
        self.assertListEqual(srw_test[140],[15])
        self.assertListEqual(srw_test[192],[13,26])
        self.assertListEqual(srw_test[203],[6, 9, 11, 12, 24, 31, 42])

if __name__ == '__main__':

    unittest.main()

    #PostcardListNew=PostcardList(None)
    #PostcardListNew.readFile('exam_postcard_list0.txt')
    #PostcardListNew.writeFile()
    #print(PostcardListNew._postcards)



