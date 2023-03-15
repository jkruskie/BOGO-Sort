List<int> list = new List<int>() {
1, 4, 2, 3, 9, 6, 8, 7, 5, 0
};
// Set text color to green
Console.ForegroundColor = ConsoleColor.Green;

// Set background color to black
Console.BackgroundColor = ConsoleColor.Black;

// Clear the screen
Console.Clear();


Console.WriteLine("Sorting...");

long iterations = 0;
ManualResetEvent stopAllThreadsEvent = new ManualResetEvent(false);

var stopwatch = System.Diagnostics.Stopwatch.StartNew();

// Create a single instance of Random
Random r = new Random();

List<Thread> threads = new List<Thread>();
for (int i = 0; i < 4; i++)
{
    int threadId = i + 1;
    threads.Add(new Thread(() => Bogo_sort(new List<int>(list), true, stopwatch, threadId, stopAllThreadsEvent, r)));
    threads[i].Start();
}

foreach (var thread in threads)
{
    thread.Join();
}

stopAllThreadsEvent.Reset();

stopwatch.Stop();

// Print the total number of iterations
Console.WriteLine("Iterations: " + iterations);
static void Bogo_sort(List<int> list, bool announce, System.Diagnostics.Stopwatch? stopwatch, int threadId, ManualResetEvent stopAllThreadsEvent, Random r)
{
    int iteration = 0;

    while (!IsSorted(list) && !stopAllThreadsEvent.WaitOne(0))
    {
        if (announce)
        {
            Print_Iteration(list, iteration, threadId);
        }
        list = Remap(list, r);
        iteration++;
    }

    if (IsSorted(list))
    {
        Console.WriteLine("Thread {0} sorted the list after {1} iterations.", threadId, iteration);
        stopAllThreadsEvent.Set();
    }
}

static void Print_Iteration(List<int> list, int iteration, int threadId)
{
    Console.WriteLine("Thread {0}: Iteration {1} = [{2}]", threadId, iteration, string.Join(", ", list));
}

static bool IsSorted(List<int> list)
{
    for (int i = 0; i < list.Count - 1; i++)
    {
        if (list[i] > list[i + 1])
        {
            return false;
        }
    }

    return true;
}

static List<int> Remap(List<int> list, Random r)
{
    int temp;
    List<int> newList = new List<int>();
    List<int> copy = new List<int>(list);

    while (copy.Count > 0)
    {
        temp = r.Next(copy.Count);
        newList.Add(copy[temp]);
        copy.RemoveAt(temp);
    }

    return newList;
}
