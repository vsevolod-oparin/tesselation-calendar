# tessellation-calendar

Compute all pentamino tesselation for the calendar.

* Text Representation: [tesselation.txt](https://github.com/vsevolod-oparin/tesselation-calendar/blob/main/tessellation.txt).
* Json Representation: [tesselation.json](https://github.com/vsevolod-oparin/tesselation-calendar/blob/main/tessellation.json).

## JSON Structure:
```
{
  date: {
    pattern: <pattern string>,
    tesselation: <tesselation string>
  }
}
```

## Project Structure

Python Notebook [Pentamino.ipynb](https://github.com/vsevolod-oparin/tesselation-calendar/blob/main/Pentamino.ipynb) computes all conversions, flipping, preparing tasks in form of bitmasks, and then parsing results of the bruteforce module. Cpp file [cruncher/main.cpp](https://github.com/vsevolod-oparin/tesselation-calendar/blob/main/cruncher/main.cpp) just bruteforce tiling. Follow the code to understand details.
