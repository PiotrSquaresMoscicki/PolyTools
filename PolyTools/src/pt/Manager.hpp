#pragma once

#include <pp/Router.hpp>
#include <pp/Common.hpp>

namespace pt
{
	// ************************************************************************************************
	// ************************************************************************************************
	// ************************************************************************************************
	class ManagerInfo
	{
	public:
		std::string name;
		int version = 0;
	};

	// ************************************************************************************************
	// ************************************************************************************************
	// ************************************************************************************************
	class Manager
	{
	public:
		// ********************************************************************************************
		// ********************************************************************************************
		// ********************************************************************************************
		class Dependencies
		{
		public:
			std::shared_ptr<pp::Router> router;
		};

		// ********************************************************************************************
		// ********************************************************************************************
		// ********************************************************************************************
		class OwnerAttorney
		{
		protected:
			static void open(Manager& subEditor, Dependencies dependencies) { subEditor.open(std::move(dependencies)); }
			static void update(Manager& subEditor, const float dt) { subEditor.update(dt); }
			static void close(Manager& subEditor) { subEditor.close(); }
		};

		// ********************************************************************************************
		virtual ~Manager() = default;

		// ********************************************************************************************
		bool isOpen() const { return m_isOpen; }

		// ********************************************************************************************
		virtual const ManagerInfo& info() const = 0;

	protected:
		virtual void onOpen() = 0;
		virtual void onUpdate(float dt) = 0;
		virtual void onClose() = 0;

		// ********************************************************************************************
		// intents & events
		std::shared_ptr<pp::Router> getRouter() { return m_deps.router; }

	private:
		// ********************************************************************************************
		void open(Dependencies dependencies)
		{
			m_deps = std::move(dependencies);
			onOpen();
			m_isOpen = true;
		}

		// ********************************************************************************************
		void update(const float dt)
		{
			onUpdate(dt);
		}

		// ********************************************************************************************
		void close()
		{
			m_isOpen = false;
			onClose();
		}

		Dependencies m_deps;
		bool m_isOpen = false;
	};

	// ************************************************************************************************
	// ************************************************************************************************
	// ************************************************************************************************
	template <typename T>
	class CreateManagerIntent
	{
	public:
		using Result = std::unique_ptr<T>;
		static inline pp::IntentInfo Info = { std::string("CreateManagerIntent_") + T::Info.name, T::Info.version };
	};
} // namespace pt