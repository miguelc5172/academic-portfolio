# TaskIt! – Technical Report

## 1. Project Overview
TaskIt! is a Trello-inspired **Kanban task manager** built with **Next.js, TypeScript, Supabase, and Tailwind CSS**.  
It was designed to demonstrate:
- **Frontend engineering** with React and TypeScript
- **Backend integration** with Supabase (Auth + Database)
- **Modern UI/UX** using animations, theming, and drag-and-drop
- **Deployment workflow** using Vercel

The project is deployed live at:  
🔗 [task-it-omega.vercel.app](https://task-it-omega.vercel.app/)

---

## 2. Architecture & Tech Stack
- **Frontend:** Next.js (React + TypeScript) with Tailwind CSS and Framer Motion for animations.
- **Backend:** Supabase (PostgreSQL + Auth).
- **Drag & Drop:** dnd-kit for draggable columns and tasks.
- **Deployment:** Vercel for CI/CD and hosting.

The app follows a **serverless full-stack model**:
- Database + auth handled entirely by Supabase
- Next.js frontend queries Supabase directly
- No custom backend required

---

## 3. Features Implemented
- 🔐 **Authentication** (Supabase Auth, email confirmation)
- 📝 **Task CRUD** (create, edit, delete)
- 🎨 **Color & Group assignment** for tasks
- 🔄 **Drag-and-drop** task movement across columns
- 📊 **Sorting** per column (A→Z, Z→A, by Group, by Color)
- 🚀 **Vercel deployment** with environment-based Supabase keys

---

## 4. Technical Choices
- **Next.js + Supabase**: Faster to prototype than building a custom backend. Supabase handled both database and auth.  
- **TypeScript**: Prevented type errors when handling tasks and state management.  
- **dnd-kit**: More lightweight and customizable than react-beautiful-dnd.  
- **Framer Motion**: For smooth animations (drag overlay, modal transitions).  
- **Tailwind CSS**: Allowed rapid styling and dark mode theming.

---

## 5. Challenges & Solutions

### Drag Overlay Alignment
- Issue: Dragged task snapped to grab-point, not cursor center.
- Solution: Custom **modifier function** to calculate offset and center overlay under cursor.

### Sorting With Group/Color
- Issue: Ungrouped/white tasks appeared in wrong order.
- Solution: Custom sort logic ensuring grouped tasks always come before ungrouped ones, and white tasks sort last for color sort.

---

## 6. Lessons Learned
- Stronger understanding of **Next.js SSR pitfalls** (hydration, client-only logic).
- Hands-on practice with **Supabase auth + queries**.
- Implemented **user-centric UX features** like theme persistence and drag-and-drop.
- Learned how to **document technical decisions** (important for collaboration).

---

## 7. Future Improvements
- Implement dark mode theme toggle.
- Add **multi-user boards** (team collaboration).
- Real-time updates via **Supabase Realtime**.
- Add **labels, due dates, and filtering** for richer task management.
- Migrate animations/UI polish into a **design system**.

---

Author: Miguel Cervantes  
Date: 2025

