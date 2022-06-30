import Cocoa

class Spaceship {
    var fuelLevel = 100
    var name = ""
    
    func cruise(){
        print("cruising is initiated for \(name)")
    }
    
    func thrust(){
        print("Rocket thrusters initiated for \(name)")
    }
}


var myShip:Spaceship = Spaceship()

myShip.name = "Tom"
myShip.cruise()
print(myShip.name)
print(myShip.fuelLevel)
