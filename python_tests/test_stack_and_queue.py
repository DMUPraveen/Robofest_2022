import os,sys

import unittest

path = os.path.join(os.path.dirname(sys.path[0]))
sys.path.append(path)
from Components.robot import Stack,Queue,PanicException


class test_Stack(unittest.TestCase):    
    def setUp(self) -> None:
        self.max_size = 10
        self.stack = Stack(self.max_size)
    def test_case_pushing(self):
        self.assertEqual(self.stack.size(),0,"Stack is not initally empty")
        self.stack.push(10)
        self.assertEqual(self.stack.size(),1,"The stack hasn't grown when 10 was pushed")
        self.stack.push(20)
        self.assertEqual(self.stack.size(),2,"The stack hasn't grown when 10 was pushed")
        self.assertEqual(self.stack.peek(),20,"Peacked value is incorrect")
        self.assertEqual(self.stack.pop(),20,"Popped value is incorrect")
        self.assertEqual(self.stack.size(),1,"The stack hasn't shrunk after pop")
        self.assertEqual(self.stack.peek(),10,"Peeked value after pop is incorrect")
        self.assertEqual(self.stack.pop(),10,"Incorrect value after second pop")
        self.assertEqual(self.stack.size(),0)
        self.assertTrue(self.stack.empty(),"Stack is not empty after pushes and two pops")
        self.stack.clear()
        self.assertTrue(self.stack.empty()) 
    def test_case_making_the_stack_full(self): 
        for _ in range(self.max_size):
            self.stack.push(10)
        self.assertTrue(self.stack.full(),"The stack is not full although it shpuld be")
        self.assertFalse(self.stack.empty(),"The stack is empty but it should be full")
        self.stack.pop()
        self.assertEqual(self.stack.size(),self.max_size-1,"Size should be reduced by one it is not")
        self.stack.clear()
        self.assertTrue(self.stack.empty(),"The stack is not empty after a clear")
    def test_panicking(self):
        self.assertTrue(self.stack.empty())
        for _ in range(self.max_size):
            self.stack.push(10) 
        self.assertRaises(PanicException,lambda : self.stack.push(10))
        self.assertTrue(self.stack.full())
        self.stack.clear()
        self.assertRaises(PanicException,lambda : self.stack.pop())
        self.assertTrue(self.stack.empty())
        
class Testing_Queue(unittest.TestCase):
    def setUp(self) -> None:
        self.max_size = 10
        self.queue = Queue(self.max_size)
    def test_pushing_and_popping(self):
        self.assertTrue(self.queue.empty()) 
        self.queue.push(10)
        self.queue.push(20)
        self.assertEqual(self.queue.size(),2)
        self.assertEqual(self.queue.peek(),10)
        self.assertEqual(self.queue.size(),2)
        self.assertEqual(self.queue.pop(),10)
        self.assertEqual(self.queue.pop(),20)
        self.assertTrue(self.queue.empty())
        self.queue.clear()
        self.assertTrue(self.queue.empty())
    def testing_cyclic_pushing_and_popping(self):
        for _ in range(10):
            self.assertTrue(self.queue.empty())
            for i in range(6):
                self.queue.push(i)
            self.assertEqual(self.queue.size(),6)
            for i in range(5):
                self.assertEqual(self.queue.pop(),i)
            self.assertEqual(self.queue.size(),1)
            arr = [5] + [i for i in range(self.max_size-1)]
            for i in arr[1:]:
                self.queue.push(i)
            self.assertTrue(self.queue.full())
            for i in range(self.max_size):
                self.assertEqual(self.queue.pop(),arr[i])
            self.assertTrue(self.queue.empty())
       
        self.queue.clear()
        self.assertTrue(self.queue.empty())
    def testing_panicking(self):
        self.assertRaises(PanicException,lambda : self.queue.pop())
        self.assertRaises(PanicException,lambda : self.queue.peek())
        for i in range(self.max_size):
            self.queue.push(i)
        self.assertRaises(PanicException,lambda : self.queue.push(10))
        self.queue.clear()
        self.assertTrue(self.queue.empty())
        self.assertRaises(PanicException,lambda : self.queue.pop())
        self.assertRaises(PanicException,lambda : self.queue.peek())
        
        
        

if __name__ == "__main__":
    unittest.main(verbosity=2)
