-- The next line may slow down your program, but it increases the power
-- of the debugger
$debug

-- Pre-defined shortcuts

setshortcut ('?', [[print([[
break(location)
cont()
delete(location)
depth([number]):number
display(string)
doalways([action])
doat(action,location)
down([number])
file():string
finish()
goto(location)
line():number
list([number],[location])
Next([number])
setshortcut(string,action)
show()
stack()
step([number])
stop([condition])
undisplay(number)
up([number])
where()
]])]])

setshortcut ('+', "up(); print('depth = '..depth())")
setshortcut ('-', "down(); print('depth = '..depth())")
setshortcut ('c', "cont()")
setshortcut ('d', "display(line)")
setshortcut ('f', "finish()")
setshortcut ('g', "goto(line)")
setshortcut ('n', "if tonumber(line) then Next(line) else Next() end")
setshortcut ('p', [[dostring(format("print('%s = '..tostring(%s))",line,line))]])
setshortcut ('q', "print('Do you really want to quit Ldb?') if read()=='y' then exit() else read('s1') end")
setshortcut ('s', "if tonumber(line) then step(line) else step() end")
setshortcut ('v', "show()")
setshortcut ('w', "where(2)")


-- Here you can call "break" to enter debug mode before running the program
--> break(<first line to be executed>, <first file to be executed>)
-- or you can call "stop" to enter debug mode now:
--> stop()
