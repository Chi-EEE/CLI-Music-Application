using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C00261172_Music_Application.DataStructure
{
    internal class CircularLinkedList<T>
    {
        public void Insert(T data)
        {
            DoubleLinkedNode<T> node = new(data, this.Head, this.Tail);
            if (this.Tail != null)
            {
                this.Tail.Next = node;
            }
            if (this.Head == null)
            {
                this.Head = node;
            }
            this.Tail = node;
            this.Count++;
        }
        /// <summary>
        /// https://stackoverflow.com/a/390974
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        private static bool Compare<T>(T x, T y) => EqualityComparer<T>.Default.Equals(x, y);
        public bool RemoveData(T data)
        {
            if (this.Count > 0)
            {
                DoubleLinkedNode<T> temp = this.Head!;
                do
                {
                    if (CircularLinkedList<T>.Compare(temp.Data, data))
                    {
                        if (this.Count == 1)
                        {
                            this.Head = null;
                            this.Tail = null;
                        }
                        else
                        {
                            temp.Next.Prev = temp.Next;
                            temp.Prev.Next = temp.Prev;
                        }
                        this.Count--;
                        return true;
                    }
                    temp = temp.Next;
                }
                while (temp != this.Tail);
            }
            return false;
        }
        public DoubleLinkedNode<T>? Head { get; private set; }
        public DoubleLinkedNode<T>? Tail { get; private set; }
        public int Count { get; private set; }
    }
}
