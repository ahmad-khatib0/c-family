```cpp
class Subject {
private:
  // List of Observers (in our application, this will be Students on wait-list)
  list<class Observer *> observers;
  int numObservers = 0;
  int subjectState = State::Initial;
  list<Observer *>::iterator newIter;

protected:
  // the constructors are declared as protected (not public). This is a design technique
  // to prevent direct instantiation of Subject while still allowing inheritance.
  Subject() = default;                // default constructor will use initialization
  Subject(int s) : subjectState(s) {} // note: numObservers set to 0 in in-class initialization
  void SetState(int s) { subjectState = s; }

public:
  int GetState() const { return subjectState; }
  int GetNumObservers() const { return numObservers; }
  virtual ~Subject() = default;
  virtual void Register(Observer *);
  virtual void Release(Observer *);
  virtual void Notify();
};
```

### **Understanding "Protected Constructors Simulate an Abstract Class"**

In your `Subject` class, the constructors are declared as **`protected`** (not `public`).
This is a design technique to **prevent direct instantiation** of `Subject` while still
allowing inheritance. Here’s what it means and why it’s used:

---

### **1. Key Behavior**

| Scenario                 | Public Constructor                          | Protected Constructor                       |
| ------------------------ | ------------------------------------------- | ------------------------------------------- |
| **Direct Instantiation** | `Subject s;` ✅ Allowed                     | `Subject s;` ❌ Compile Error               |
| **Inheritance**          | `class Derived : public Subject { ... }` ✅ | `class Derived : public Subject { ... }` ✅ |

---

### **2. Why Use Protected Constructors?**

#### **Goal**:

- Make `Subject` act like an **abstract class** (cannot be instantiated directly) **without** using pure virtual functions (`= 0`).
- Force users to **only instantiate derived classes** (e.g., `ConcreteSubject`).

#### **How It Works**:

- By making constructors `protected`, only derived classes can call them.
- The base class (`Subject`) cannot be created standalone.

---

### **3. Example**

#### **Base Class (`Subject`)**:

```cpp
class Subject {
protected:
    Subject() = default;  // Protected constructor
    Subject(int s) : subjectState(s) {}
public:
    virtual ~Subject() = default;
    // ... other methods ...
};
```

#### **Derived Class (`ConcreteSubject`)**:

```cpp
class ConcreteSubject : public Subject {
public:
    ConcreteSubject() : Subject() {}       // ✅ Can call protected constructor
    ConcreteSubject(int s) : Subject(s) {} // ✅
};
```

#### **Attempting Direct Instantiation**:

```cpp
int main() {
    Subject s;          // ❌ Error: Constructor is protected
    ConcreteSubject cs; // ✅ Works
}
```

---

### **4. Comparison to Abstract Classes**

| Feature           | Pure Virtual (`= 0`) Abstract Class | Protected Constructor "Simulated" Abstract Class   |
| ----------------- | ----------------------------------- | -------------------------------------------------- |
| **Instantiation** | ❌ Cannot instantiate               | ❌ Cannot instantiate (compile-time error)         |
| **Inheritance**   | ✅ Must override pure virtuals      | ✅ No requirement to override methods              |
| **Use Case**      | Enforce interface implementation    | Control construction (e.g., singleton, base class) |

---

### **5. Why This Design?**

1. **Flexibility**:
   - Avoids forcing derived classes to override methods (unlike pure virtual functions).
   - Still prevents misuse by disallowing direct `Subject` instances.

2. **Real-World Use Cases**:
   - **Observer Pattern**: Your `Subject` is meant to be extended (e.g., by `WaitlistSubject`).
   - **Singletons**: Ensure only one instance exists.
   - **Base Classes**: Where only derived classes should be instantiated.

---

### **6. Key Takeaways**

- **Protected constructors** simulate abstraction by restricting instantiation to derived classes.
- Unlike pure virtual functions, this approach **doesn’t enforce method overrides**.
- Useful when you want a **base class** to exist only as part of a derived object.

This technique is common in design patterns (e.g., Observer, Singleton) and frameworks where base classes are "incomplete" by design.
